package arafat.rng70.Mediator;

import arafat.rng70.Providers.*;

import java.util.Queue;

public class ServiceMediator implements Mediator{

//    Queue<Providers>JPDCProvider = new Queue<Providers>();
//    Queue<Providers>JRTAProvider = new Queue<Providers>();
//    Queue<Providers>JTRCProvider = new Queue<Providers>();
//    Queue<Providers>JWSAProvider = new Queue<Providers>();
    public void init(){
        System.out.println("All four services are initiated through mediator");
    }
    @Override
    public void requestService(String serviceName, String provideName){
        System.out.println("p");
    }

    @Override
    public void serveService(String serviceName, String providerName) {
        System.out.println("K");
    }
}
