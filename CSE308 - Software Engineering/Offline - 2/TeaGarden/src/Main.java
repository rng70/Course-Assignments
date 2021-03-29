import java.util.Scanner;
import Package.Builder.Hardware;
import Package.WebServers.WebServers;

public class Main {

  public static void main(String[] args) {
    SubscriptionBuilder subscriptionBuilder = new SubscriptionBuilder();
    Hardware hardwareComponent;
    System.out.println("Enter the Package name(Silver || Gold || Diamond || Platinum)");
    Scanner scanner = new Scanner(System.in);

    String packageName = scanner.nextLine();
    if (packageName.equalsIgnoreCase("silver")) {
      hardwareComponent = subscriptionBuilder.generateSilverUser();
    } else if (packageName.equalsIgnoreCase("gold")) {
      hardwareComponent = subscriptionBuilder.generateGoldUser();
    } else if (packageName.equalsIgnoreCase("diamond")) {
      hardwareComponent = subscriptionBuilder.generateDiamondUser();
    } else {
      hardwareComponent = subscriptionBuilder.generatePlatinumUser();
    }

    System.out.println("Enter Internet Connection Type(Wifi || GSM || Ethernet)");
    scanner = new Scanner(System.in);

    String internetConnectionType = scanner.nextLine();
    subscriptionBuilder.setInternetConnection(internetConnectionType);

    System.out.println("Enter preferred web framework(Django || Spring || Laravel)");
    scanner = new Scanner(System.in);

    String webServer = scanner.nextLine();
    WebServers webServers = subscriptionBuilder.getWebServersFactory(webServer);
    System.out.println("<<- === === === === === === === === === === === === === === === === === === === === === === === === ->>");
    hardwareComponent.showHardwareComponents();
    webServers.showWebServerInfo();
    System.out.println("<<- === === === === === === === === === === === === === === === === === === === === === === === === ->>");

  }
}
