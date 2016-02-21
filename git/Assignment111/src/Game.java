import java.io.*;
import java.util.*;

public class Game{
   public static void main(String args[]){
      Kakro kakgame=new Kakro("game1.txt");
      kakgame.Display();
      kakgame.startGame();
   }
}