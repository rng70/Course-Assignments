package arafat.rng70;

public class ServiceOffer {
    private String serviceName;
    private String needServiceFor;

    public ServiceOffer(String serviceName, String needServiceFor){
        this.serviceName = serviceName;
        this.needServiceFor = needServiceFor;
    }
    public String getService(){
        return this.serviceName;
    }
}
