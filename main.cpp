#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const size_t MAX_SIZE = 256;
const size_t MAX_EXTENSION = 3;
const char* forbidden =  "*<>?|\""; //на запрещенные символы

int main()
{
    char text[MAX_SIZE];
    cout << "Enter file name: ";
    fgets(text, MAX_SIZE, stdin);
    char* filename = text;
    filename[strlen(filename) - 1] = '\0';
    while(true) {
        if( strcspn( filename, forbidden ) == strlen( filename ) ) ; //
        else {
            cout << "Invalid format";
            break;
        }

        if( strchr( filename, ':' ) == nullptr ) ;
        else {
            char* colon = strchr(filename,':');
            if( colon - filename + 1 <= 1 ) {
                cout << "Invalid format"; //на двоеточие
                break;
            }
                if( isalpha( filename[colon - filename - 1] ) > 0 &&
                    filename[colon - filename + 1] == '\\')
                    colon = strchr(colon + 1, ':'); // на
                else {
                    cout << "Invalid format";
                    break;
                }

        }

        if( strrchr( filename, '.' ) == nullptr )
            strcat( filename, ".txt" );

        else {
            char* ext = strrchr( filename, '.' );
            for( int i = 1; ext[i] != '\0'; i ++ )
                *(ext + i) = char(tolower(*(ext + i)));
            if( strncmp( ext, ".txt", MAX_EXTENSION + 1 ) == 0 ) ; //проверка на расширение
            else {
                cout << "Invalid format";
                break;
            }
        }

        FILE* file = fopen( filename, "r" );
        if( file == nullptr ) {
            cout << "Invalid file name";
            break;
        }
        fseek( file, 0, SEEK_END ); // переставляет указатель на конец файла
        long filesize = ftell( file ); //запоминается конец файла

        char* filedata = new char[filesize];
        rewind( file ); // возвращает указатель в начала файла
        fread( filedata, 1, filesize, file );
        filedata[filesize] = '\0'; //начинает запись, из открытого файла

        char STR[MAX_SIZE];
        cout << "Enter string: ";
        fgets(STR, MAX_SIZE, stdin);
        char* str = STR;
        *( str + strlen(str) - 1 ) = '\0'; //обращается по указателю к концу значений строки

        int occur = 0;
        while( *filedata != '\0'  ) {
           if( strncmp( filedata, str, strlen(str) ) != 0 )
                filedata += 1;
           else {
                occur ++;
                filedata += 1;
           }
        }
        cout << "Occurance number: " << occur;

        delete[] filedata;
        fclose( file );
        break;
    }
    return 0;
}
