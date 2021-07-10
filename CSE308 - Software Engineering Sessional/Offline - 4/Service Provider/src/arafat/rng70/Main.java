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
        JPDC jpdc = new JPDC(mediator);
        JRTA jrta = new JRTA(mediator);
        JTRC jtrc = new JTRC(mediator);
        JWSA jwsa = new JWSA(mediator);
        System.out.println("<-- ---------------- -->");

        Scanner scanner = new Scanner(System.in);

        /* ****************************************** */
        /*   The while loop below takes user input    */
        /*      from console and handle to call       */
        /*   appropriate method through mediator      */
        /*                                            */
        /*                                            */
        /*                                            */
        /* ****************************************** */
        while(scanner.hasNextLine()){
            String[] input = scanner.nextLine().split(" ");
            if(input[0].equalsIgnoreCase("exit")){
                break;
            }
            if(input[0].equalsIgnoreCase("init")){
                mediator.init();
            }
            if(input[0].equalsIgnoreCase("jpdc")){
                if(input[1].equalsIgnoreCase("serve")){
                    jpdc.serveService();
                }else{
                    jpdc.requestService(input[1]);
                }
            }else if(input[0].equalsIgnoreCase("jrta")){
                if(input[1].equalsIgnoreCase("serve")){
                    jrta.serveService();
                }else{
                    jrta.requestService(input[1]);
                }
            }else if(input[0].equalsIgnoreCase("jtrc")){
                if(input[1].equalsIgnoreCase("serve")){
                    jtrc.serveService();
                }else{
                    jtrc.requestService(input[1]);
                }
            }else if(input[0].equalsIgnoreCase("jwsa")){
                if(input[1].equalsIgnoreCase("serve")){
                    jwsa.serveService();
                }else{
                    jwsa.requestService(input[1]);
                }
            }
        }
    }
}
