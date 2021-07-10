package Packages.Aesthetics;

public abstract class Aesthetics {
  String font, style, color;

  public abstract void setFont();

  public void setStyle() {
    style = "Normal";
  }

  public void setColor() {
    color = "Blue";
  }

  public void showAesthetics() {
    System.out.println(
        "Font: " + this.font + "\nStyle: " + this.style + "\nColor: " + this.color);
  }
}
