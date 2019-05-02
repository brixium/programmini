/*Scrivere un programma Java che legge una stringa e un carattere da input e restituisca una stringa risultante costituita solo da i caratteri della stringa originaria presenti dalla prima occorrenza del carattere inserito in poi. Il programma non deve distinguere tra caratteri maiuscoli o minuscoli
Esempio:
	stringa: Esame DI Informatica
	carattere: i
	stringa risultante: Informatica
*/
import java.io.*;

public class q3{
	public static void main(String [] args){
		try{
/*
Try e catch sono due istruzioni per gestire le eccezioni in java (non so se l'avete fatto però se è una cosa nuova puoi toglierle dal programma e mettere scrivere public static void main(String [] args) throws IOException{}	e funziona tutto lo stesso
*/

/*Dichiarazione var*/
			String testo, risultato; 
			char in; /*Carattere inserito*/
			int i, slen;
			boolean flag;
/*Inizializzazione var*/
			i=0;
			risultato = "";
			flag = false;
			InputStreamReader isr = new InputStreamReader(System.in);
			BufferedReader br = new BufferedReader(isr);
/*Lettura da console*/
			System.out.print("Inserisci la stringa: ");
			testo = br.readLine();
			System.out.print("Inserisci un carattere: ");
			in = br.readLine().charAt(0);
/*Soluzione del problema*/
			slen = testo.length();
			for(i=0; i<slen && !flag; i++)
				if((testo.charAt(i)+"").equalsIgnoreCase(""+in))
					flag = true;
			for( ; i<slen; i++)
				risultato = risultato + testo.charAt(i);
/*Stampa ris*/
			System.out.println(risultato);
		}catch(IOException ex){
			ex.printStackTrace();
		}
		return ;
	}
}
