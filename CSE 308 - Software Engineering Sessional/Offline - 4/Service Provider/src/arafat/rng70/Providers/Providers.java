package arafat.rng70.Providers;

import arafat.rng70.Mediator.Mediator;

public abstract class Providers {
    private Mediator mediator;
    private String providerName;

    public Providers(Mediator mediator){
        this.mediator = mediator;
    }
    public void requestService(String serviceName){
        mediator.requestService(serviceName, this.providerName);
    }
    public void serveService(String serviceName){
        mediator.serveService(serviceName, this.providerName);
    }
    public void setProviderName(String providerName){
        this.providerName = providerName;
    }

}
