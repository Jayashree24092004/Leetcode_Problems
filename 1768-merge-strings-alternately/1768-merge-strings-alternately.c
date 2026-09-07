

char * mergeAlternately(char * word1, char * word2){
    int n=strlen(word1);
    int m =strlen(word2);
    int i,j,k=0;
    char *result=(char*)malloc((m+n+1) *sizeof (char));
    while(i<n && j<m){
        result[k++]=word1[i++];
        result[k++]=word2[j++];
    }
    while(i<n){
        result[k++]=word1[i++];
    }
    while(j<m){
        result[k++]=word2[j++];
    }
    result[k]='\0';
    return result;

}