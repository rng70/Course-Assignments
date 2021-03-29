import java.util.Scanner;

import Packages.Editor.Editor;

public class Main {
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    String fileName;

    while (true) {
      System.out.println("Enter file extension(C || C++ || Python || Q to Quit): ");
      fileName = scanner.nextLine();
      if (fileName.equalsIgnoreCase("Q")) break;

      Editor editor = new Editor();
      editor = editor.getEditor(fileName);
      System.out.println(
          "<<- === === === === === === === === === === === === === === === === === === === === === === === === ->>");
      editor.showEditorInfo();
      System.out.println(
          "<<- === === === === === === === === === === === === === === === === === === === === === === === === ->>");
    }
  }
}
