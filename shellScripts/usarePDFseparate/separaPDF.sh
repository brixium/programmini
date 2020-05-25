#! /usr/bin/env sh

INPUT_FILE_NAME=""
INPUT_FILE_NAME_LENGTH=0
INPUT_DIRECTORY_NAME="."
INPUT_DIRECTORY_NAME_LENGTH=0
INIZIO_O_FINE="fine"
OUTPUT_DIRECTORY_NAME="."
OUTPUT_DIRECTORY_NAME_LENGTH=0
OUTPUT_FILE_NAME=""
OUTPUT_FILE_NAME_LENGTH=0

### INSERIMENTO NOME DIRECTORY
echo -n "Inserisci il percorso in cui si trova il file di origine. Se il file è in questa directory, ovvero $(pwd) , digita un punto fisso: "
read INPUT_DIRECTORY_NAME
INPUT_DIRECTORY_NAME_LENGTH=$(echo $INPUT_DIRECTORY_NAME | awk '{print length}')
while [ $INPUT_DIRECTORY_NAME_LENGTH -lt 1 ]
do
	echo -n "Non hai inserito il nome della directory, rifallo: "
	read INPUT_DIRECTORY_NAME
	INPUT_DIRECTORY_NAME_LENGTH=$(echo $INPUT_DIRECTORY_NAME | awk '{print length}')
done
while ! [ -d $INPUT_DIRECTORY_NAME ]
do
	echo -n "La cartella non esiste, inserisci nuovamente il nome:"
	read INPUT_DIRECTORY_NAME
	INPUT_DIRECTORY_NAME_LENGTH=$(echo $INPUT_DIRECTORY_NAME | awk '{print length}')
done

### INSERIMENTO NOME DEL FILE

echo -n "Inserisci il nome del file originale SENZA percorso: "
read INPUT_FILE_NAME
INPUT_FILE_NAME_LENGTH=$(echo $INPUT_FILE_NAME | awk '{print length}')
#echo "IFLEN: $INPUT_FILE_NAME_LENGTH"
while [ $INPUT_FILE_NAME_LENGTH -lt 1 ]
do
	echo -n "Non hai inserito il nome del file, rifallo: "
	read INPUT_FILE_NAME
	INPUT_FILE_NAME_LENGTH=$(echo $INPUT_FILE_NAME | awk '{print length}')
done
#echo $INPUT_FILE_NAME | wc -c 
#echo $INPUT_FILE_NAME | awk '{print length}'
#echo "Input file: $INPUT_FILE_NAME"

### adesso output directory 

echo -n "Inserisci il percorso (DIRECTORY) in cui si troveranno i file di destinazione. Se i file saranno in questa directory, ovvero $(pwd) , digita un punto fisso: "
read OUTPUT_DIRECTORY_NAME
OUTPUT_DIRECTORY_NAME_LENGTH=$(echo $OUTPUT_DIRECTORY_NAME | awk '{print length}')
while [ $OUTPUT_DIRECTORY_NAME_LENGTH -lt 1 ]
do
	echo -n "Non hai inserito il nome della directory, rifallo: "
	read OUTPUT_DIRECTORY_NAME
	OUTPUT_DIRECTORY_NAME_LENGTH=$(echo $OUTPUT_DIRECTORY_NAME | awk '{print length}')
done
if ! [ -d $OUTPUT_DIRECTORY_NAME ];
then
	echo -n "La cartella non esiste, vuoi crearla? (_Sì_/No)"
	read SCELTA
	if [ "$SCELTA" = "SI" ] || [ "$SCELTA" = "SÌ" ] || [ "$SCELTA" = "S" ] || [ "$SCELTA" = "s" ] || [ "$SCELTA" = "si" ] || [ "$SCELTA" = "sì" ];
	then
		mkdir OUTPUT_DIRECTORY_NAME
		# considerare problemi di creazione in futuro
		if [ $? != 0 ]; 
		then
			echo "Si è verificato un errore e la cartella non è stata creata :("
		else
			echo "Ho correttamente creato la cartella $OUTPUT_DIRECTORY_NAME"
		fi
	fi
	OUTPUT_DIRECTORY_NAME_LENGTH=$(echo $OUTPUT_DIRECTORY_NAME | awk '{print length}')
fi

### adesso output file

echo -n "Inserisci il nome dei file di destinazione SENZA percorso: "
read OUTPUT_FILE_NAME
OUTPUT_FILE_NAME_LENGTH=$(echo $OUTPUT_FILE_NAME | awk '{print length}')
while [ $OUTPUT_FILE_NAME_LENGTH -lt 1 ]
do
	echo -n "Non hai inserito il nome dei file, rifallo: "
	read OUTPUT_FILE_NAME
	OUTPUT_FILE_NAME_LENGTH=$(echo $OUTPUT_FILE_NAME | awk '{print length}')
done

#adesso pattern: inizio o fine

echo -n "Dove vuoi inserire la numerazione dei file? [Inizio/_Fine_/Altro] "

