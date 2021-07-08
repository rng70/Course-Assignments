package arafat.rng70;

import java.util.ArrayList;
import java.util.Collections;

public class Sorting_UnitTest {

    public ArrayList<Integer> sort(ArrayList<Integer> listToSort){
        for(int i=0;i<listToSort.size();i++){
            int pos = i;
            for(int j=i+1;j<listToSort.size();j++){
                if(listToSort.get(pos) > listToSort.get(j)){
                    pos = j;
                }
            }
            if(pos!=i){
                Collections.swap(listToSort, i, pos);
            }
        }

        return listToSort;
    }
}
