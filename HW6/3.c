#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#define DATABASE_PATH "playlist.dat"
#define NAME_LEN 100
#define ARTIST_LEN 100

typedef struct Song {
    char name[NAME_LEN];
    char artist[ARTIST_LEN];
    int duration;      // in seconds
    int isFavorite;
} Song;


int parse_duration(char dur[]);
int count_args(char* line);


void add_song(char *line);
void delete_song(char *line);
void star_song(char *line);
void unstar_song(char *line);

void list_songs();
void filter_favorites();
void sort_by_name();
void sort_by_artist();
void sort_by_duration();
void calculate_signature();
void calculate_entropy();

int main(){
    FILE *fp = fopen("playlist.dat", "a");
    fclose(fp);
    freopen("output.txt", "w", stdout);
    char line[1000];


    while(fgets(line, sizeof(line), stdin)){
        line[strcspn(line, "\n")] = '\0';
        if(strcmp(line, "exit") == 0)break;
        if(strncmp(line, "add", 3) == 0){
            add_song(line);
        }else if(strncmp(line, "delete", 6) == 0){
            delete_song(line);
        }else if(strncmp(line, "star", 4) == 0){
            star_song(line);
        }else if(strncmp(line, "unstar", 4) == 0){
            unstar_song(line);
        }else if(strncmp(line, "list", 4) == 0){
            list_songs();
        }else if(strncmp(line, "filter_favorites", 16) == 0){
            filter_favorites();
        }else if(strncmp(line, "sort_name", 9) == 0){
            sort_by_name();
        }else if(strncmp(line, "sort_artist", 11) == 0){
            sort_by_artist();
        }else if(strncmp(line, "sort_duration", 13) == 0){
            sort_by_duration();
        }else if(strncmp(line, "playlist_signature", 17) == 0){
            calculate_signature();
        }else if(strncmp(line, "playlist_entropy", 16) == 0){
            calculate_entropy();
        }
    }
    return 0;
}


int parse_duration(char dur[]){
    enum FORMAT{
        SECONDS,
        MINUTES,
    };
    int i = 0;
    int format = SECONDS;
    while(dur[i] != '\0'){
        if(dur[i] == ':'){
            if(format == MINUTES)return -1;
            format = MINUTES;
        }else if(!isdigit(dur[i])){
            return -1;
        }
        i++;
    }
    if(format == SECONDS){
        int seconds;
        sscanf(dur, "%d", &seconds);
        return seconds;
    }
    int seconds = 0;
    int minutes = 0;
    int res = sscanf(dur, "%d:%d", &minutes, &seconds);
    if(res != 2)return -1;
    if(seconds >= 60 || seconds < 0 || minutes < 0 || minutes > 99) return -1;
    return 60 * minutes + seconds;
}
int count_args(char *line){
    int i, words = 0;
    int inWord = 0;
    for (i = 0; line[i] != '\0'; i++) {
        if (!isspace(line[i])) {
            if (!inWord) {
                words++;
                inWord = 1;
            }
        } else {
            inWord = 0;
        }
    }
    return words;
}

void add_song(char *line){
    Song s;
    memset(s.name, '\0', NAME_LEN);
    memset(s.artist, '\0', ARTIST_LEN);
    char dur[100] = {'\0'};
    int res = sscanf(line, "add %99s %99s %99s", s.name, s.artist, dur);
    if(res != 3){
        printf("Invalid add command.\n");
        return;
    }
    int duration_in_seconds = parse_duration(dur);
    if(duration_in_seconds == -1){
        printf("Invalid duration format: %s\n", dur);
        return;
    }
    s.duration = duration_in_seconds;
    s.isFavorite = 0;
    FILE *db = fopen(DATABASE_PATH, "ab");
    fwrite(&s, sizeof(Song), 1, db);
    fclose(db);

    printf("Song added: %s by %s\n", s.name, s.artist);
}

void delete_song(char *line){
    char name[NAME_LEN];
    sscanf(line, "delete %s", name);
    
    FILE *db = fopen(DATABASE_PATH, "r+b");
    FILE *temp = fopen("temp.dat", "wb");

    Song currentSong; 
    int found = 0;
    while(fread(&currentSong, sizeof(Song), 1, db) == 1){
        if(strcmp(name, currentSong.name) != 0){
            fwrite(&currentSong, sizeof(Song), 1, temp);
        }else{
            found = 1;
        }
    }
    if(found){
        printf("Deleted: %s\n", name);
    }else{
        printf("Song not found: %s\n", name);
    }
    fclose(db);
    fclose(temp);
    remove(DATABASE_PATH);
    rename("temp.dat", DATABASE_PATH);
}

void star_song(char *line){
    char name[NAME_LEN];
    sscanf(line, "star %s", name);

    FILE *db = fopen(DATABASE_PATH, "rb+");

    Song currentSong;
    int count = 0;
    int found = 0;
    while(fread(&currentSong, sizeof(Song), 1, db) == 1){
        if(strcmp(currentSong.name, name) == 0){
            found = 1;
            break;
        }
        count++;
    }
    if(found){
        currentSong.isFavorite = 1;
        fseek(db, count * sizeof(Song), SEEK_SET);
        fwrite(&currentSong, sizeof(Song), 1, db);
        printf("Starred: %s\n", name);
    }
    fclose(db);
}

void unstar_song(char *line){
    char name[NAME_LEN];
    sscanf(line, "unstar %s", name);

    FILE *db = fopen(DATABASE_PATH, "rb+");

    Song currentSong;
    int count = 0;
    int found = 0;
    while(fread(&currentSong, sizeof(Song), 1, db) == 1){
        if(strcmp(currentSong.name, name) == 0){
            found = 1;
            break;
        }
        count++;
    }
    if(found){
        currentSong.isFavorite = 0;
        fseek(db, count * sizeof(Song), SEEK_SET);
        fwrite(&currentSong, sizeof(Song), 1, db);
        printf("Unstarred: %s\n", name);
    }
    fclose(db);
}

void list_songs(){
    FILE *db = fopen(DATABASE_PATH, "rb");
    Song s;
    int is_empty = 1;
    while(fread(&s, sizeof(Song), 1, db) == 1){
        printf("%s | %s | %d | %s\n", s.name, s.artist, s.duration, s.isFavorite ? "Favorite" :"Normal" );
        is_empty = 0;
    }
    if(is_empty){
        printf("Playlist is empty.\n");
    }
    fclose(db);
}

void filter_favorites(){
    FILE *db = fopen(DATABASE_PATH, "rb");
    Song s;
    int is_empty = 1;
    while(fread(&s, sizeof(Song), 1, db) == 1){
        if(s.isFavorite){
            printf("%s | %s | %d | %s\n", s.name, s.artist, s.duration, s.isFavorite ? "Favorite" :"Normal" );
            is_empty = 0;
        }
    }
    if(is_empty){
        printf("No favorites found.\n");
    }
    fclose(db);
}

int cmpByName(const void *a, const void *b) {
    int namecmp = strcmp(((Song *)a)->name, ((Song *)b)->name);
    if(namecmp == 0){
        return strcmp(((Song *)a)->artist, ((Song *)b)->artist);
    }
    return namecmp;
}
void sort_by_name(){
    FILE *db = fopen(DATABASE_PATH, "rb");
    fseek(db, 0, SEEK_END);
    int count = ftell(db) / sizeof(Song);
    if(count == 0)return;
    Song *playlist = malloc(count * sizeof(Song));

    fseek(db, 0, SEEK_SET);
    fread(playlist, sizeof(Song), count, db);
    fclose(db);

    qsort(playlist, count, sizeof(Song), cmpByName);
    
    db = fopen(DATABASE_PATH, "wb");
    fwrite(playlist, sizeof(Song), count, db);
    fclose(db);

    free(playlist);

    printf("Sorted by name.\n");
}

int cmpByArtist(const void *a, const void *b) {
    int artcmp = strcmp(((Song *)a)->artist, ((Song *)b)->artist);
    if(artcmp == 0){
        return strcmp(((Song *)a)->name, ((Song *)b)->name);
    }
    return artcmp;
}
void sort_by_artist(){
    FILE *db = fopen(DATABASE_PATH, "rb");
    fseek(db, 0, SEEK_END);
    int count = ftell(db) / sizeof(Song);
    if(count == 0)return;
    Song *playlist = malloc(count * sizeof(Song));

    fseek(db, 0, SEEK_SET);
    fread(playlist, sizeof(Song), count, db);
    fclose(db);

    qsort(playlist, count, sizeof(Song), cmpByArtist);
    
    db = fopen(DATABASE_PATH, "wb");
    fwrite(playlist, sizeof(Song), count, db);
    fclose(db);

    free(playlist);

    printf("Sorted by artist.\n");
}


int cmpByDuration(const void *a, const void *b) {
    if(((Song *)a)->duration > ((Song *)b)->duration)return 1;
    if(((Song *)a)->duration < ((Song *)b)->duration)return -1;

    int artcmp = strcmp(((Song *)a)->artist, ((Song *)b)->artist);
    if(artcmp == 0){
        return strcmp(((Song *)a)->name, ((Song *)b)->name);
    }
    return artcmp;   
    
}
void sort_by_duration(){
    FILE *db = fopen(DATABASE_PATH, "rb");
    fseek(db, 0, SEEK_END);
    int count = ftell(db) / sizeof(Song);
    if(count == 0)return;
    Song *playlist = malloc(count * sizeof(Song));

    fseek(db, 0, SEEK_SET);
    fread(playlist, sizeof(Song), count, db);
    fclose(db);

    qsort(playlist, count, sizeof(Song), cmpByDuration);
    
    db = fopen(DATABASE_PATH, "wb");
    fwrite(playlist, sizeof(Song), count, db);
    fclose(db);

    free(playlist);

    printf("Sorted by duration.\n");
}

void calculate_signature(){
    FILE *db  = fopen(DATABASE_PATH, "rb");
    int signature = 0;
    Song s;
    int i = 0;
    while(fread(&s, sizeof(Song), 1, db) == 1){
        int name_len = strlen(s.name);
        int h_name = 0;
        for(int j = 0; j < name_len; j++){
            h_name += (int)(s.name[j]) * (j + 1);
        }

        int artist_len = strlen(s.artist);
        int h_artist = 0;
        for(int j = 0; j < artist_len; j++){
            h_artist += (int)(s.artist[j]) * (j + 1);
        }

        int song_hash = 31 * h_name + 17 * h_artist + 13 * s.duration + 7 * s.isFavorite;
        signature ^= (song_hash << (i % 16));
        i++;
    }
    if(i == 0){
        printf("Playlist signature: 0\n");
    }else{
        printf("Playlist signature: %llu\n", signature);
    }
    fclose(db);
}

void calculate_entropy(){
    FILE *db = fopen(DATABASE_PATH, "rb");
    fseek(db, 0, SEEK_END);
    int songs_count = ftell(db) / sizeof(Song);
    
    if(songs_count == 0){
        printf("Playlist entropy: 0.000\n");
        fclose(db);
        return;
    } 
    
    Song *all_songs = malloc(sizeof(Song) * songs_count);
    
    fseek(db, 0, SEEK_SET);
    fread(all_songs, sizeof(Song), songs_count, db);

    qsort(all_songs, songs_count, sizeof(Song), cmpByArtist);

    int *songs_by_artists = malloc(sizeof(int) * songs_count);
    memset(songs_by_artists, 0, sizeof(int) * songs_count);
    int artist_count = 0;


    for(int i = 0; i < songs_count; i++){
        if(i == 0 || strcmp(all_songs[i].artist, all_songs[i - 1].artist) != 0){
            artist_count++;
        }
        songs_by_artists[artist_count - 1]++;
    }


    long double h = 0.000;

    for(int i = 0; i < artist_count; i++){
        long double pi = (long double)songs_by_artists[i] / (long double)songs_count;
        h -= pi * log2(pi);
    }

    printf("Playlist entropy: %.3Lf\n", h);

    free(songs_by_artists);
    free(all_songs);
    fclose(db);
}