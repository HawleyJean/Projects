import java.io.*;
import java.util.*;


public class Kakro{
	private Cell[][] gameboard;
	private int curr;
	private int curr2;
   private int col;
   private int row;
	
	public Kakro(String filename){
	try{
   //The file with the numerals, depicting the cells, and board
		FileReader fin = new FileReader(filename);
		
		//A scanner which will withdraw the values found in the cell
		Scanner src = new Scanner(fin);
		
		
		
		//making the dimensions columns by rows
		
		row=src.nextInt();
		col=src.nextInt();
		System.out.println("The dimensions are "+col+" "+row);
		
		// dimensions are finished
		gameboard=new Cell[row][col];
		
		while(src.hasNext()){
			
			for(int i=0; i<row; i++){ //I is Rows
			
				for(int j=-0; j<col; j++){ // J is columns
						curr=src.nextInt();
		//putting the cells in the gameboard
						if(curr==-1){
							//white cells
							gameboard[i][j]=new Cell(false, curr, 11,11);
						}
						else{
							curr2=src.nextInt();
							//black cells
							gameboard[i][j]=new Cell(true, 11, curr2,curr);
						}
						
				}//column counter
	}//rows counter
			}//whiel loop
		fin.close();
		src.close();
      }
		
	//our catch methods just in case we cant find our file
	catch(FileNotFoundException e){
		System.out.println("File wasnt found");
	}
	catch(IOException e1){
	System.out.println("File not found");
	}
	}
   
   
   //This method will start the game once the file has been read
   public void startGame(){
      boolean gamewon=false;
      Scanner kbd=new Scanner(System.in);
      int r, c, v;
      
      
      //The gamewon boolean function will keep this while loop running. As long as the game hasnt been won, the boolean will stay
      //false and therefore the loop will continue
      while(!gamewon){
    	System.out.println("\nEnter 3 numeric values, ROW, COLUMN, VALUE, Respectivley \n");  
    	  //We display the board over as the 
      this.Display();
      System.out.println("\n");
      r=kbd.nextInt();
      c=kbd.nextInt();
      v=kbd.nextInt();
      if((v>9||v<1)||(c>=col||c<1)||(r>=row||r<1)){
         System.out.println("invalid input, please retype your values");      
         }
         else{
            if(gameboard[r][c].isBlack())
               System.out.println("You cannot input a value in this block!");
            else{
               gameboard[r][c].AttemptWhiteBlock(v);
            }
         }
   }
   }
   
   
   public void Display(){
   for(int i=0; i<row; i++){
    for(int j=0; j<col; j++){
      System.out.print(gameboard[i][j]);
   }
   System.out.println();
   }
   }
	}


