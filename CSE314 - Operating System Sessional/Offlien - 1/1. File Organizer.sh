#!/bin/bash

er=()
ig_er=()
ep=("$@")
directory='./'
input='b'

function show_manual(){
    echo "File Organizer 0.1 (created by rng70)
Usage: nothing.sh [directory name](optional) [file-name-with-extension-type](txt)
    directory-name: full path of the directory[no tailing slash(/)] where the script will be run
                    default directory is current working directory
    file-name: absolute path of the text file which contains the extension to ignore
               if absolute path is not provided then file will be searched only in the
               parent directory of the current working directory where the script is run"
}

function show_success_msg(){
    d_output=$1
    echo "File Organizer 0.1 (created by rng70)
Success: Files were organized successfully
        you can see the files in the output directory.
        To see file type the following command
        
            cd ${d_output} && ls 
            
        and also see the summary in output.csv file. 
        To see summary type the following command
            
            cd ${d_output} && cd ../ && nano output.csv
            
        Hope you enjoy the file ogranizer"
}

function createCSV(){
    csv_file_dir="../output.csv"
    touch "${csv_file_dir}"
    cur_dir1="../output_dir/"
    cur_dir2=$PWD
    cd $cur_dir1
    count=0
    
    echo "file types, no_of_files" >> "${csv_file_dir}"
    
    for i in "${er[@]}"
        do
           count=($(find . -type f -name "*.${i}" -exec printf x \; | wc -c))
           echo "${i}, $count" >> "${csv_file_dir}"
        done
        
    count=($(find . -type f ! -name "*.*" -exec printf x \; | wc -c))
    echo "others, $count" >> "${csv_file_dir}"
    
    declare -i otherCount=0
    count=0
    cd $cur_dir2

    for i in "${ig_er[@]}"
        do
           count=($(find . -type f -name "*.${i}" -exec printf x \; | wc -c))
           otherCount=`expr $otherCount + $count`
        done    
    echo "ignored, $otherCount" >> "${csv_file_dir}"
    
    show_success_msg $cur_dir1 
}

function print_number_of_arguments(){
    if [ ${#ep[@]} -eq 0 ]
        then
            show_manual
            exit 1
    fi

    if [ ${#ep[@]} -eq 1 ]
        then
            if [ "${ep[0]:(-3)}" == "txt" ]
                then
                    input="${ep[0]}"
                    FILE="${input}"
                    
                    if [ ! test -f "$FILE" ]
                    then
                        input="./${input}"
                        echo "${input}"
                    fi
            else
                show_manual
                exit 1
            fi
            
    elif [ ${#ep[@]} -eq 2 ]
        then
            directory="${ep[0]}"
            input="${ep[1]}"
            
            #if [ "${input}" == "input.txt" ]
            #    then
            #        input="../${ep[1]}"
            #fi
            if [ "${directory:(-1)}" == "/" ]
                then
                    show_manual
                    exit 1
            else
                directory="${directory}/"
            fi
                
            
            #FILE="${input}"
            # echo "Here ${input}"       
            if [ ! -f ${input} ]
            then       
                input="../${input}"
                #echo "${input}"
            fi        
    fi        
}

function read_from_file(){
    input=$1
    #echo "${input}"
    while IFS= read -r line
    do
        line="$(echo -e "${line}" | tr -d '[:space:]')"
        [[ $line = *[![:space:]]* ]] && ig_er+=($line)
    done < "$input"    
}

function find_all_extension(){
    er=($(find . -type f -name "*.*" | awk -F. '{print $NF}' | sort -u))
}

function disjoint_set(){
    for i in "${!ig_er[@]}"
    do
        for j in "${!er[@]}"
        do
            if [ "${ig_er[$i]}" == "${er[$j]}" ]
            then
                unset er[$j]
            fi
       done
   done    
}

function print_to_array(){
    local -n myarr=$1
    direc=$2
    desc_file=$3

    newArray=()
    for i in "${myarr[@]}"
        do
            str=$i
            newStr="${direc}${str:1}"
            newArray+=("${newStr}")
        done
    
    printf "%s\n" "${newArray[@]}" > "${desc_file}"
    #print_the_array myarr $desc_file
}

function print_the_array(){
    local -n myar=$1
    filename=$2
    echo $filename
    printf "%s\n" "${myar[@]}" > "${filename}"

    for i in "${myar[@]}"
    do
        echo $i
    done
}

function move_files(){
    echo "${directory}"
    find ${directory} -name "*.${ep[@]}" -exec bash -c '
        echo "treating file $1 in bash, from path : ${1%/*}" 
    ' -- {} \;
}

function move_files_from_subdirectory_also(){
    mkdir -p "../output_dir/"
    result=${PWD##*/}
    
    for ii in "${er[@]}"
        do  
            dirc="../output_dir/${ii}/"
            mkdir -p "${dirc}"
            desc_file="${dirc}desc_${ii}.txt"
            touch "${desc_file}"
            filename=()

            while IFS= read -r -d $'\0'
                do
                    filename+=("$REPLY")
                done < <(find . -name "*.${ii}" -print0)
            
            print_to_array filename $result $desc_file
       
            find . -name "*.${ii}" -exec cp "{}" --target-directory="${dirc}" \;
        done
    
    dirc="../output_dir/others/"    
    mkdir -p "${dirc}"
    desc_file="${dirc}desc_others.txt"
    touch "${desc_file}"
    otherArray=()
    
    while IFS= read -r -d $'\0'
        do
            otherArray+=("$REPLY")
        done < <(find . -type f ! -name "*.*" -print0)
            
    print_to_array otherArray $result $desc_file
    find . -type f ! -name "*.*" -exec cp "{}" "${dirc}" \;
}

print_number_of_arguments
cd ${directory}
read_from_file ${input}
find_all_extension
disjoint_set
move_files_from_subdirectory_also
createCSV
