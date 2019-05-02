/*
Scrivere un programma in Java che chieda all'utente di inserire una sequenza di interi positivi, chiedendo prima quanti numeri si voglia inserire e, al termine dell'inserimento dell'intera sequenza, stampi una stringa che indichi se tutti i numeri inseriti sono dispari e primi o, al contrario, se non lo sono.
*/
import java.io.*;
public class q4{
	public static void main(String [] args) throws IOException{
		int nel, i, num; /*N elem, contatore, singolo numero*/
		boolean flag; /*Indica il possible risultato*/
		String lettura; /*la serie di numeri la registro qui*/
		String[] strs;/*qui salvo ciascuno numero in una posizione dell'array di stringhe*/

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));/*inizializzo lo standard input*/
		
		System.out.print("Quanti numeri vuoi inserire? ");
		nel = Integer.parseInt(br.readLine()); /*leggo il numero di el*/
		System.out.print("Inserisci i numeri: ");
		lettura = br.readLine(); /*leggo i numeri sotto forma di stringa*/
		strs = lettura.trim().split("\\s+"); /*spezzo la stringa quando trovo uno o più spazi, salvo il risultato in strs*/
		
		flag = true;
		for(i=0; i<nel && flag; i++){
			num = Integer.parseInt(strs[i]); /*Converto in int i numeri*/
			if(num % 2 == 0 || !isPrimo(num))
				flag = false;
		}
		if(flag)
			System.out.println("Tutti i numeri inseriti sono dispari e primi");
		else
			System.out.println("Non tutti i numeri inseriti sono dispari e primi");
		return ;
	}
	/*Ho fatto un metodo che verifica se un numero è primo*/
	static boolean isPrimo(int n){
		int i;
		i = 2;
		while((n/2) >= i){
			if(n % i == 0)
				return false;
			i++;
		}
		return true;
	}
}
