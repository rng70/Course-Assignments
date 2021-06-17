package Observer;

public interface Observer {
    /* ********************************************** */
    /*                                                */
    /*  The three trigger operation is given for the  */
    /*    I is given for increase the stock price     */
    /*    D is given for decrease the stock price     */
    /*    C is given for changing the stock count     */
    /*                                                */
    /* ********************************************** */
    void triggerOperation(String triggerMode);

    /* ********************************************** */
    /*                                                */
    /* After every trigger operation a message to the */
    /*  Subscriber is needed to be sent which is done */
    /*                 by this method                 */
    /*                                                */
    /* ********************************************** */
    void sendStockToAll();

}
