package Package.WebServers;

public class WebServersFactory {
    public WebServers getWebServers(String webServerName){
        if(webServerName.equalsIgnoreCase("django")){
            return new Django();
        }else if(webServerName.equalsIgnoreCase("laravel")){
            return new Laravel();
        }else{
            return new Spring();
        }
    }
}
