package Packages.Editor;

import Packages.Parser.Parser;
import Packages.Aesthetics.Aesthetics;

public interface InfoFactory {
    Parser getParser(String parserFileExtension);
    Aesthetics getHighlighter(String highlighterFileExtension);
}
