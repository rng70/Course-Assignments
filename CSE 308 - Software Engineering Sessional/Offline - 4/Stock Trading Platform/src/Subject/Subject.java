package Subject;

import java.util.ArrayList;

public interface Subject {
    ArrayList<Stocks> allStocks = new ArrayList<Stocks>();

    /* ********************************************** */
    /*                                                */
    /*  At the beginning the stocks price need to be  */
    /*  read from a file to show the stock prices to  */
    /*     all the users when they first login        */
    /*                                                */
    /* ********************************************** */
//    void readStocks();

    /* ********************************************** */
    /*                                                */
    /*  The three trigger operation is given for the  */
    /*    I is given for increase the stock price     */
    /*    D is given for decrease the stock price     */
    /*    C is given for changing the stock count     */
    /*                                                */
    /* ********************************************** */
    void triggerOperation(char triggerMode, String stockName, double stockPriceOrCount);

    /* ********************************************** */
    /*                                                */
    /* After every trigger operation a message to the */
    /*  Subscriber is needed to be sent which is done */
    /*                 by this method                 */
    /*                                                */
    /* ********************************************** */
    void sendStockToAll();
}
