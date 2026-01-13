#include<stdio.h>
#include<curl/curl.h>
/*
Function: write_callback
----------------------
Callback function to write server response to output
Parameters: 
    ptr: points to the data
    size: size of each unit of data
    nmemb: number of such units in the chunk
    stream: the pointer set with CURLOPT_WRITEDATA
Returns: 
    int: the number of bytes successfully handled (size*nmemb)
*/
size_t write_callback(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    return fwrite(ptr, size, nmemb, stream);
}
/*
Function: stock_data_scraper
------------------------------
It makes a secure http GET request to the stock api endpoint for current stock price and stores the response to stock_data.txt
Parameters: 
    symbol: string containing stock symbol
Returns: 
    int: 0 on success, 1 if unable to open stock_data.txt, -1 if curl handle not returned, -2 if any error arises during the easy session
*/
int stock_data_scraper(char symbol[20])
{
    CURL *curl; // libcurl handle
    CURLcode result; // libcurl result code
    FILE* fp;
    char url[200];
    struct curl_slist* headers=NULL; // list to store custom htttp headers
    snprintf(url, sizeof(url), "https://query1.finance.yahoo.com/v8/finance/chart/%s.NS?interval=1d&range=1d",symbol); // adjusting api endpoint according to stock

    fp=fopen("stock_data.txt","w"); // file in which fetched data would be written

    if(!fp){
        fprintf(stderr, "Failed to open file for writing\n");
        return 1;
    }
    
    curl_global_init(CURL_GLOBAL_DEFAULT); // initializes libcurl globally
    curl=curl_easy_init(); // initializes libcurl easy session and returns handle for it
    if(curl==NULL)
    {
        fprintf(stderr,"HTTP request failed\n");
        return -1;
    }
    // helps curl request behave like browser
    headers=curl_slist_append(headers, "User-Agent: Mozilla/5.0");
    curl_easy_setopt(curl, CURLOPT_URL ,url); // sets the target url
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); // informs libcurl to use custom header list that is created
    curl_easy_setopt(curl, CURLOPT_CAINFO, "cacert.pem"); // verifies https using a CA cert (trusted Certificate Authority(CA) certificates)

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback); // sets the write callback to handle the response
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp); // sets the file pointer to pass to the callback

    result=curl_easy_perform(curl); // performs the request, result will get the return code
    if(result!= CURLE_OK) // checks for errors
    {
        fprintf(stderr, "Error: %s\n",curl_easy_strerror(result));
        return -2;
    }
    curl_slist_free_all(headers); // frees m/m allocated for headers
    curl_easy_cleanup(curl); // cleanup the curl session
    fclose(fp);
    curl_global_cleanup(); // global libcurl cleanup
    return 0;
}