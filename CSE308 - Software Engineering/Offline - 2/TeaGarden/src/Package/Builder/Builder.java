package Package.Builder;

import Package.WeightMeasurement.WeightMeasurement;
import Package.InternetConnection.InternetConnection;

public interface Builder {
  Hardware getHardware();

  void setDisplay();

  void setIdentifier();

  void makeController();

  void setStorageMedium();

  void setAdditionalControllers();

  void setInternetConnectivity(InternetConnection ic);

  void setWeightMeasurementTool(WeightMeasurement tool);
}
