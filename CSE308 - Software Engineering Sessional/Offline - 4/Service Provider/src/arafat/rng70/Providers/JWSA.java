package arafat.rng70.Providers;

import arafat.rng70.Mediator.Mediator;

public class JWSA extends Providers{
    public JWSA(Mediator mediator){
        super(mediator, "JWSA");
        System.out.println("\tJWSA Initialized");
    }
}
