package arafat.rng70;


import arafat.rng70.Mediator.ServiceMediator;
import arafat.rng70.Providers.JPDC;
import arafat.rng70.Providers.JRTA;
import arafat.rng70.Providers.JTRC;
import arafat.rng70.Providers.JWSA;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        ServiceMediator mediator = new ServiceMediator();
        JPDC jpdc = new JPDC(this);
        JRTA jrta = new JRTA(this);
        JTRC jtrc = new JTRC(this);
        JWSA jwsa = new JWSA(this);

        Scanner scanner = new Scanner(System.in);
        while(scanner.hasNextLine()){
            String[] input = scanner.nextLine().split(" ");

            if(input[0].equalsIgnoreCase("jpdc")){
                if(input[1].equalsIgnoreCase("serve")){
                    jpdc.serveService(input[1]);
                }else{
                    jpdc.requestService(input[1]);
                }
            }else if(input[0].equalsIgnoreCase("jrta")){
                if(input[1].equalsIgnoreCase("serve")){
                    jrta.serveService(input[1]);
                }else{
                    jrta.requestService(input[1]);
                }
            }else if(input[0].equalsIgnoreCase("jtrc")){
                if(input[1].equalsIgnoreCase("serve")){
                    jtrc.serveService(input[1]);
                }else{
                    jtrc.requestService(input[1]);
                }
            }else if(input[0].equalsIgnoreCase("jwsa")){
                if(input[1].equalsIgnoreCase("serve")){
                    jwsa.serveService(input[1]);
                }else{
                    jwsa.requestService(input[1]);
                }
            }
        }
    }
}
