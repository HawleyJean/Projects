import java.io.*;

import java.util.*;


public class Cell{
	
	private boolean isblack;
	private int val;
	private int down;
	private int right;

	public Cell(boolean black, int val, int down, int right){
		if(black){
			isblack=black;
			this.down=down;
			this.right=right;
			this.val=-30;
		}
		else if(!black){
			isblack=black;
			this.down=-1;
			this.right=-1;
			this.val=val;
		}
	}
	
	public boolean isBlack(){
		return isblack;
	}
	
	public void AttemptWhiteBlock(int value){
		if(isblack){
			System.out.print("This is a black block, its values cannot be changed");
		}
		else
		val=value;
	}
	
	public Cell(){
	}
	
	public String toString(){
	String k;
   	if(isblack){
			k="|_"+down+"\\"+right+"_|  ";
		}
		else{
			if(val==-1)
			k="|_____|  ";
			else
				k="|__"+val+"__|  ";
		}
		return k;
	}
}