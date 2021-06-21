package arafat.rng70.Providers;

import arafat.rng70.Mediator.Mediator;

public abstract class Providers {
    private Mediator mediator;
    private String name;

    public Providers(Mediator mediator, String name){
        this.name = name;
        this.mediator = mediator;
    }
    /* ****************************************** */
    /*                                            */
    /*     The method handle all request for      */
    /*    different services through mediator     */
    /*                                            */
    /* ****************************************** */
    public void requestService(String serviceName){
        mediator.requestService(serviceName, this.name);
    }

    /* ****************************************** */
    /*                                            */
    /*     The method handle all serve request    */
    /*  for different services through mediator   */
    /*                                            */
    /* ****************************************** */
    public void serveService(){
        mediator.serveService(name);
    }
}
