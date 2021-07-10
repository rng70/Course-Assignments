package Packages.Editor;

import Packages.Aesthetics.Aesthetics;
import Packages.Parser.Parser;

public class Editor {
  private Editor editor = null;
  static Parser parser;
  static Aesthetics aesthetics;

  public Editor getEditor(String fileTypeExtension) {
    if (editor == null) editor = new Editor();
    InterfaceFactory interfaceFactory = new InterfaceFactory();
    parser = interfaceFactory.getInfoFactory("Parser").getParser(fileTypeExtension);
    aesthetics = interfaceFactory.getInfoFactory("Aesthetics").getHighlighter(fileTypeExtension);
    return editor;
  }

  public void showEditorInfo() {
    parser.showParsingInfo();
    aesthetics.setFont();
    aesthetics.setStyle();
    aesthetics.setColor();
    aesthetics.showAesthetics();
  }
}
