package arafat.rng70;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.*;
import java.util.concurrent.ThreadLocalRandom;

import java.util.stream.Collectors;

import static org.junit.jupiter.api.Assertions.*;

class MainTest {
    Sorting_UnitTest sorting_unitTest;
    @BeforeEach
    void setUp() {
        sorting_unitTest = new Sorting_UnitTest();
    }

    private void printList(ArrayList<Integer> list){
        for (int i: list){
            System.out.print(i + " ");
        }
        System.out.println();
    }

    private ArrayList<Integer> generateNegativeNumbers(int size, boolean isSorted, boolean isAsc){
        Random random = new Random();
        ArrayList<Integer>queue = new ArrayList<>();
        if(isSorted){
            int number = random.nextInt(2499)-2500;
            for(int i=0;i<size;i++){
                queue.add(number);
                number -= i;
            }
            if(isAsc){
                Collections.reverse(queue);
            }
        }else{
            for(int i=0;i<size;i++){
                queue.add(random.nextInt(2499)-2500);
            }
        }

        return queue;
    }

    private ArrayList<Integer> generatePositiveNumbers(int size, boolean isSorted, boolean isAsc){
        Random random = new Random();
        ArrayList<Integer>queue = new ArrayList<>();
        if(isSorted){
            int number = random.nextInt(1000)+1000;
            for(int i=0;i<size;i++){
                queue.add(number);
                number += i;
            }
            if(!isAsc){
                Collections.reverse(queue);
            }
        }else{
            for(int i=0;i<size;i++){
                queue.add(random.nextInt(2500));
            }
        }

        return queue;
    }

    private ArrayList<Integer> generateList(int size, boolean isSizeRandom, boolean isRandom, boolean isSorted, boolean isAsc, boolean isNeg){
        ArrayList<Integer> list = new ArrayList<>();
        if(isSizeRandom){
            size = ThreadLocalRandom.current().nextInt() % 1000;

            if(isNeg){
                list = generateNegativeNumbers(size, isSorted, isAsc);
            }else {
                list = generatePositiveNumbers(size, isSorted, isAsc);
            }
        }else if(isRandom){
            if(isNeg){
                list = generateNegativeNumbers(size, isSorted, isAsc);
            }else {
                list = generatePositiveNumbers(size, isSorted, isAsc);
            }
        }

        return list;
    }

    @Test
    public void checkBlankList() throws Exception{
        ArrayList<Integer> localCopy = new ArrayList<>();
        ArrayList<Integer> listToSort = new ArrayList<>(localCopy);
        sorting_unitTest.sort(listToSort);

        assertTrue(localCopy.size() == listToSort.size() && listToSort.containsAll(localCopy) && localCopy.containsAll(listToSort));
        assertTrue(listToSort.stream().sorted().collect(Collectors.toList()).equals(listToSort));
    }

    @Test
    public void listWithSingleElement() throws Exception{
        ArrayList<Integer> localCopy = new ArrayList<>(Collections.singletonList(1));
        ArrayList<Integer> listToSort = new ArrayList<>(localCopy);
        sorting_unitTest.sort(listToSort);

        assertTrue(localCopy.size() == listToSort.size() && listToSort.containsAll(localCopy) && localCopy.containsAll(listToSort));
        assertTrue(listToSort.stream().sorted().collect(Collectors.toList()).equals(listToSort));
    }

    @Test
    public void listWithTwoElement() {
        ArrayList<Integer> localCopy = new ArrayList<>(Arrays.asList(3, 1));
        ArrayList<Integer> listToSort = new ArrayList<>(localCopy);
        sorting_unitTest.sort(listToSort);

        assertTrue(localCopy.size() == listToSort.size() && listToSort.containsAll(localCopy) && localCopy.containsAll(listToSort));
        assertTrue(listToSort.stream().sorted().collect(Collectors.toList()).equals(listToSort));
    }

    @Test
    public void randomlyInitializedSizeList() {
        ArrayList<Integer> localCopy = generateList(0, true, true, false, false, false);
        ArrayList<Integer> listToSort = new ArrayList<>(localCopy);

        sorting_unitTest.sort(listToSort);

        assertTrue(localCopy.size() == listToSort.size() && listToSort.containsAll(localCopy) && localCopy.containsAll(listToSort));
        assertTrue(listToSort.stream().sorted().collect(Collectors.toList()).equals(listToSort));
    }

    @Test
    public void randomlyInitializedList() {
        ArrayList<Integer> localCopy = generateList(20, false, true, false, false, false);
        ArrayList<Integer> listToSort = new ArrayList<>(localCopy);

        sorting_unitTest.sort(listToSort);

        assertTrue(localCopy.size() == listToSort.size() && listToSort.containsAll(localCopy) && localCopy.containsAll(listToSort));
        assertTrue(listToSort.stream().sorted().collect(Collectors.toList()).equals(listToSort));
    }

    @Test
    public void randomlyInitializedSizeList() {
        ArrayList<Integer> localCopy = generateList(0, true, true, false, false, false);
        ArrayList<Integer> listToSort = new ArrayList<>(localCopy);

        sorting_unitTest.sort(listToSort);

        assertTrue(localCopy.size() == listToSort.size() && listToSort.containsAll(localCopy) && localCopy.containsAll(listToSort));
        assertTrue(listToSort.stream().sorted().collect(Collectors.toList()).equals(listToSort));
    }
}