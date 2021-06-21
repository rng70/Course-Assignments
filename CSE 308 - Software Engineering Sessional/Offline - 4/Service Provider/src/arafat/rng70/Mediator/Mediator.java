package arafat.rng70.Mediator;

public interface Mediator {
    void requestService(String serviceName, String providerName);
    void serveService(String serviceName, String providerName);
}
