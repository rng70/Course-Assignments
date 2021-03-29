import Package.Builder.*;
import Package.WebServers.*;
import Package.InternetConnection.*;
import Package.WeightMeasurement.LoadSensor;
import Package.WeightMeasurement.WeightModule;

public class SubscriptionBuilder {

  Builder builder;
  WebServersFactory webServersFactory = new WebServersFactory();

  private void commonConstructor(){
    builder.setDisplay();
    builder.setIdentifier();
    builder.makeController();
    builder.setStorageMedium();
    builder.setAdditionalControllers();
  }

  public Hardware generateSilverUser() {
    builder = new ATMega32();
    commonConstructor();
    builder.setWeightMeasurementTool(new LoadSensor());
    return builder.getHardware();
  }

  public Hardware generateGoldUser() {
    builder = new ArduinoMega();
    commonConstructor();
    builder.setWeightMeasurementTool(new WeightModule());
    return builder.getHardware();
  }

  public Hardware generateDiamondUser() {
    builder = new RaspberryPi();
    commonConstructor();
    builder.setWeightMeasurementTool(new LoadSensor());
    return builder.getHardware();
  }

  public Hardware generatePlatinumUser() {
    builder = new RaspberryPi();
    commonConstructor();
    builder.setWeightMeasurementTool(new WeightModule());
    return builder.getHardware();
  }

  public WebServers getWebServersFactory(String webServersFactoryName) {
    return this.webServersFactory.getWebServers(webServersFactoryName);
  }

  public void setInternetConnection(String str) {
    if (str.equalsIgnoreCase("wifi")) builder.setInternetConnectivity(new WirelessFidelity());
    else if (str.equalsIgnoreCase("gsm")) builder.setInternetConnectivity(new GSMModule());
    else if (str.equalsIgnoreCase("ethernet")) builder.setInternetConnectivity(new Ethernet());
  }
}
