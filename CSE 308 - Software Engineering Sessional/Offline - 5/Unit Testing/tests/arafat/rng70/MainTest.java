package arafat.rng70;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.*;

import java.util.stream.Collectors;

import static org.junit.jupiter.api.Assertions.*;

/**
 * In this testing assignment "A sorting routine" was tested
 *
 * Total 16 test case was covered
 *
 * Blank List
 * List with exactly 1 element
 * List with exactly 2 element
 * Size of the list was randomly initialized
 * Number of the was randomly generated
 *          --> Numbers are equal
 *                  --> Positive
 *                  --> Negative
 *
 *          --> Numbers are not equal
 *                  --> Positive Only
 *                      --> Sorted
 *                          --> Ascending Order
 *                          --> Descending Order
 *                      --> Not sorted
 *                  --> Negative Only
 *                      --> Sorted
 *                          --> Ascending Order
 *                          --> Descending Order
 *                      --> Not sorted
 *                 --> Positive and Negative Mixed
 *                      --> Sorted
 *                          --> Ascending Order
 *                          --> Descending Order
 *                      --> Not sorted
 * List has repeated numbers
 */

class MainTest {
    Sorting_UnitTest sorting_unitTest;
    @BeforeEach
    void setUp() {
        sorting_unitTest = new Sorting_UnitTest();
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

    private ArrayList<Integer> generateEqualNumber(int size, boolean isPos){
        int number;
        Random random = new Random();
        ArrayList<Integer> equalList = new ArrayList<>();
        if(isPos){
            number = random.nextInt(1000)+10;
        }else{
            number = random.nextInt(500)-1000;
        }

        for(int i=0;i<size;i++){
            equalList.add(number);
        }

        return equalList;
    }

    private ArrayList<Integer> generateList(int size, boolean isSorted, boolean isAsc, boolean isNeg){
        ArrayList<Integer> list;
            if(isNeg){
                list = generateNegativeNumbers(size, isSorted, isAsc);
            }else {
                list = generatePositiveNumbers(size, isSorted, isAsc);
            }
        return list;
    }

    /**
     * Case-1:
     * Testing the sorting routine
     * with a blank list
     */
    @Test
    public void checkBlankList(){
        ArrayList<Integer> localCopy = new ArrayList<>();
        ArrayList<Integer> listToSort = new ArrayList<>(localCopy);
        sorting_unitTest.sort(listToSort);

        assertTrue(localCopy.size() == listToSort.size() && listToSort.containsAll(localCopy) && localCopy.containsAll(listToSort));
        assertEquals(listToSort.stream().sorted().collect(Collectors.toList()), listToSort);
    }

    /**
     * Case-2:
     * Testing the sorting routine
     * with a list of single element
     */
    @Test
    public void listWithSingleElement() {
        ArrayList<Integer> localCopy = new ArrayList<>(Collections.singletonList(1));
        ArrayList<Integer> listToSort = new ArrayList<>(localCopy);
        sorting_unitTest.sort(listToSort);

        assertTrue(localCopy.size() == listToSort.size() && listToSort.containsAll(localCopy) && localCopy.containsAll(listToSort));
        assertEquals(listToSort.stream().sorted().collect(Collectors.toList()), listToSort);
    }

   /** Case-3:
   * Testing the sorting routine
   * with a list of two elements
   */
  @Test
  public void listWithTwoElement() {
        ArrayList<Integer> localCopy = new ArrayList<>(Arrays.asList(3, 1));
        ArrayList<Integer> listToSort = new ArrayList<>(localCopy);
        sorting_unitTest.sort(listToSort);

        assertTrue(localCopy.size() == listToSort.size() && listToSort.containsAll(localCopy) && localCopy.containsAll(listToSort));
        assertEquals(listToSort.stream().sorted().collect(Collectors.toList()), listToSort);
    }

    /**
     * Case-4:
     * Testing the sorting routine
     * with a list which size was
     * randomly generated
     * and all elements are randomly ordered
     */
    @Test
    public void randomlyInitializedSizeList() {
        Random random = new Random();
        int size = random.nextInt(50) + 10;
        ArrayList<Integer> localCopy = generateList(size, false, false, false);
        ArrayList<Integer> listToSort = new ArrayList<>(localCopy);

        sorting_unitTest.sort(listToSort);

        assertTrue(localCopy.size() == listToSort.size() && listToSort.containsAll(localCopy) && localCopy.containsAll(listToSort));
        assertEquals(listToSort.stream().sorted().collect(Collectors.toList()), listToSort);
    }

    /**
     * Case-5;
     * Testing the sorting routine
     * with a list whose numbers were randomly generated
     * and all are positive
     */
    @Test
    public void randomlyGeneratedPositiveList() {
        ArrayList<Integer> localCopy = generateList(25, false, false, false);
        ArrayList<Integer> listToSort = new ArrayList<>(localCopy);

        sorting_unitTest.sort(listToSort);

        assertTrue(localCopy.size() == listToSort.size() && listToSort.containsAll(localCopy) && localCopy.containsAll(listToSort));
        assertEquals(listToSort.stream().sorted().collect(Collectors.toList()), listToSort);
    }

    /**
     * Case-6:
     * Testing the sorting routine
     * with a list whose numbers were randomly generated
     * and all are negative
     */
    @Test
    public void randomlyGeneratedNegativeList() {
        ArrayList<Integer> localCopy = generateList(25, false, false, true);
        ArrayList<Integer> listToSort = new ArrayList<>(localCopy);

        sorting_unitTest.sort(listToSort);

        assertTrue(localCopy.size() == listToSort.size() && listToSort.containsAll(localCopy) && localCopy.containsAll(listToSort));
        assertEquals(listToSort.stream().sorted().collect(Collectors.toList()), listToSort);
    }

     /**
     * Case-7:
     * Testing the sorting routine
     * with a list whose numbers were randomly generated
     * and both positive and negative numbers are included
     */
     @Test
    public void randomlyGeneratedBothPositiveNegativeList(){
         ArrayList<Integer> localCopy = generateList(25, false, false, true);
         localCopy.addAll(generateList(25, false, false, false));
         Collections.shuffle(localCopy);
         ArrayList<Integer> listToSort = new ArrayList<>(localCopy);

         sorting_unitTest.sort(listToSort);

         assertTrue(localCopy.size() == listToSort.size() && listToSort.containsAll(localCopy) && localCopy.containsAll(listToSort));
         assertEquals(listToSort.stream().sorted().collect(Collectors.toList()), listToSort);
     }

    /**
     * Case-8:
     * Testing the sorting routine with
     * randomly generated sorted positive numbers with
     * ascending order
     */
    @Test
    public void randomlyGeneratedSortedPositiveAscNumber(){
        ArrayList<Integer> localCopy = generateList(25, true, true, false);
        ArrayList<Integer> listToSort = new ArrayList<>(localCopy);

        sorting_unitTest.sort(listToSort);

        assertTrue(localCopy.size() == listToSort.size() && listToSort.containsAll(localCopy) && localCopy.containsAll(listToSort));
        assertEquals(listToSort.stream().sorted().collect(Collectors.toList()), listToSort);
    }

    /**
     * Case-9:
     * Testing the sorting routine with
     * randomly generated sorted positive numbers with
     * descending order
     */
    @Test
    public void randomlyGeneratedSortedPositiveDescNumber(){
        ArrayList<Integer> localCopy = generateList(25, true, false, false);
        ArrayList<Integer> listToSort = new ArrayList<>(localCopy);

        sorting_unitTest.sort(listToSort);

        assertTrue(localCopy.size() == listToSort.size() && listToSort.containsAll(localCopy) && localCopy.containsAll(listToSort));
        assertEquals(listToSort.stream().sorted().collect(Collectors.toList()), listToSort);
    }

    /**
     * Case-10:
     * Testing the sorting routine with
     * randomly generated sorted negative numbers with
     * ascending order
     */
    @Test
    public void randomlyGeneratedSortedNegativeAscNumber(){
        ArrayList<Integer> localCopy = generateList(25, true, true, true);
        ArrayList<Integer> listToSort = new ArrayList<>(localCopy);

        sorting_unitTest.sort(listToSort);

        assertTrue(localCopy.size() == listToSort.size() && listToSort.containsAll(localCopy) && localCopy.containsAll(listToSort));
        assertEquals(listToSort.stream().sorted().collect(Collectors.toList()), listToSort);
    }

    /**
     * Case-11:
     * Testing the sorting routine with
     * randomly generated sorted positive numbers with
     * descending order
     */
    @Test
    public void randomlyGeneratedSortedNegativeDescNumber(){
        ArrayList<Integer> localCopy = generateList(25, true, false, true);
        ArrayList<Integer> listToSort = new ArrayList<>(localCopy);

        sorting_unitTest.sort(listToSort);

        assertTrue(localCopy.size() == listToSort.size() && listToSort.containsAll(localCopy) && localCopy.containsAll(listToSort));
        assertEquals(listToSort.stream().sorted().collect(Collectors.toList()), listToSort);
    }

    /**
     * Case-12:
     * Testing the sorting routine
     * with a list whose numbers were randomly generated
     * and both positive and negative numbers are included
     * with sorted order in ascending order
     */
    @Test
    public void randomlyGeneratedBothPositiveNegativeSortedAscList(){
        ArrayList<Integer> localCopy = generateList(25, true, true, true);
        localCopy.addAll(generateList(25, true, true, false));
        Collections.shuffle(localCopy);
        ArrayList<Integer> listToSort = new ArrayList<>(localCopy);

        sorting_unitTest.sort(listToSort);

        assertTrue(localCopy.size() == listToSort.size() && listToSort.containsAll(localCopy) && localCopy.containsAll(listToSort));
        assertEquals(listToSort.stream().sorted().collect(Collectors.toList()), listToSort);
    }

    /**
     * Case-13:
     * Testing the sorting routine
     * with a list whose numbers were randomly generated
     * and both positive and negative numbers are included
     * with sorted order in descending order
     */
    @Test
    public void randomlyGeneratedBothPositiveNegativeSortedDescList(){
        ArrayList<Integer> localCopy = generateList(25, true, false, true);
        localCopy.addAll(generateList(25, true, false, false));
        Collections.shuffle(localCopy);
        ArrayList<Integer> listToSort = new ArrayList<>(localCopy);

        sorting_unitTest.sort(listToSort);

        assertTrue(localCopy.size() == listToSort.size() && listToSort.containsAll(localCopy) && localCopy.containsAll(listToSort));
        assertEquals(listToSort.stream().sorted().collect(Collectors.toList()), listToSort);
    }

    /**
     * Case-14:
     * Testing the sorting routine
     * with a list whose numbers were randomly generated
     * and all numbers are same and positive
     */
    @Test
    public void randomlyGeneratedSamePositiveNumberList(){
        ArrayList<Integer> localCopy = generateEqualNumber(25, true);
        ArrayList<Integer> listToSort = new ArrayList<>(localCopy);

        sorting_unitTest.sort(listToSort);

        assertTrue(localCopy.size() == listToSort.size() && listToSort.containsAll(localCopy) && localCopy.containsAll(listToSort));
        assertEquals(listToSort.stream().sorted().collect(Collectors.toList()), listToSort);
    }

    /**
     * Case-15:
     * Testing the sorting routine
     * with a list whose numbers were randomly generated
     * and all numbers are same and negative
     */
    @Test
    public void randomlyGeneratedSameNegativeNumberList(){
        ArrayList<Integer> localCopy = generateEqualNumber(25, false);
        ArrayList<Integer> listToSort = new ArrayList<>(localCopy);

        sorting_unitTest.sort(listToSort);

        assertTrue(localCopy.size() == listToSort.size() && listToSort.containsAll(localCopy) && localCopy.containsAll(listToSort));
        assertEquals(listToSort.stream().sorted().collect(Collectors.toList()), listToSort);
    }

    /**
     * Case-16:
     * Testing the sorting routine
     * with a list whose numbers were randomly generated
     * and at least some elements are repeated
     */
    @Test
    public void randomlyGeneratedListWithRepeatedNumber(){
        ArrayList<Integer> localCopy = generateEqualNumber(25, true);
        localCopy.addAll(localCopy);
        ArrayList<Integer> listToSort = new ArrayList<>(localCopy);

        sorting_unitTest.sort(listToSort);

        assertTrue(localCopy.size() == listToSort.size() && listToSort.containsAll(localCopy) && localCopy.containsAll(listToSort));
        assertEquals(listToSort.stream().sorted().collect(Collectors.toList()), listToSort);
    }
}