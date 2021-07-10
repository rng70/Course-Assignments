package arafat.rng70.Mediator;

public interface Mediator {
    void init();
    void requestService(String serviceName, String providerName);
    void serveService(String providerName);
}
