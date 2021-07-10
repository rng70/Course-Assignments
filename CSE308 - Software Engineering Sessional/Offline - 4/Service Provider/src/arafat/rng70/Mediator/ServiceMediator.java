package arafat.rng70.Mediator;

import java.util.LinkedList;
import java.util.Queue;

public class ServiceMediator implements Mediator{

    Queue<String>JPDCProvider = new LinkedList<>();
    Queue<String>JRTAProvider = new LinkedList<>();
    Queue<String>JTRCProvider = new LinkedList<>();
    Queue<String>JWSAProvider = new LinkedList<>();

    @Override
    public void init(){
        System.out.println("All four services are initiated through mediator");
    }

    /* ****************************************** */
    /*                                            */
    /*        The method handle all request       */
    /*      for different services which were     */
    /*         requested through mediator         */
    /*                                            */
    /* ****************************************** */
    @Override
    public void requestService(String serviceName, String providerName){
        if(serviceName.equalsIgnoreCase("Power")){
            JPDCProvider.add(providerName);
        }else if(serviceName.equalsIgnoreCase("Telecom")){
            JTRCProvider.add(providerName);
        }else if(serviceName.equalsIgnoreCase("Water")){
            JWSAProvider.add(providerName);
        }else{
            JRTAProvider.add(providerName);
        }
        System.out.println(providerName + " requests for " + serviceName + " service");
    }

    /* ****************************************** */
    /*                                            */
    /*     The method handle all serve request    */
    /*      for different services which were     */
    /*         requested through mediator         */
    /*                                            */
    /* ****************************************** */
    @Override
    public void serveService(String providerName) {
        if(providerName.equalsIgnoreCase("JPDC")){
            System.out.println(providerName + " serves the request of " + JPDCProvider.poll());
        }else if(providerName.equalsIgnoreCase("JRTA")){
            System.out.println(providerName + " serves the request of " + JRTAProvider.poll());
        }else if(providerName.equalsIgnoreCase("JTRC")){
            System.out.println(providerName + " serves the request of " + JTRCProvider.poll());
        }else{
            System.out.println(providerName + " serves the request of " + JWSAProvider.poll());
        }
    }
}
