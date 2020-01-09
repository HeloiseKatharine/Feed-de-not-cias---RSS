/*Feed de notícias - RSS*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Canal
{
    char Titulo[1000];
    char Descricao[1000];
    char Link[1000];
};

struct Noticias
{
    char Titulo[1000];
    char Descricao[1000];
    char Link[1000];
    char Data[1000];
};

struct Noticias noticias[1000];
struct Canal canal;

int quantidade_tag(char vetor[], char tag[])
{
    int i=0, j=0, k=0;
    int tam_vetor = strlen(vetor);
    int tam_tag = strlen(tag);
    int match;
    int quant=0;

    for (i=0; i < tam_vetor-tam_tag+1; i++)
    {
        match = 1;
        k = i;

        for (j=0; j < tam_tag; j++)
        {
            if (tag[j] != vetor[k])
            {
                match = 0;
                break;
            }
            k++;
        }
        if (match == 1)
        {
            quant++;
        }
    }
    return quant;
}

int *encotra_tag(char vetor[], char tag[], int quant) //retora a quantidade de tags
{
    int tam_vetor = strlen(vetor);
    int tam_tag = strlen(tag);
    int i, j, k;
    int match;
    int *vetor_indices = malloc((quant)*sizeof(int));
    int cont=0;

    for (i=0; i < tam_vetor-tam_tag+1; i++)
    {
        match = 1;
        k = i;

        for (j=0; j < tam_tag; j++)
        {
            if (tag[j] != vetor[k])
            {
                match = 0;
                break;
            }
            k++;
        }
        if (match == 1)
        {
            vetor_indices[cont] = i;
            cont++;
        }
    }
    return vetor_indices; // retornar um vetor
}

void arquivo_html(struct Canal canal, struct Noticias *noticias, int quant)//criar um arquico html
{
    int i=0;

    FILE *texto_rss;

    texto_rss = fopen("rss.html", "w+"); //abrindo arquivo para leitura e grava��o.

    if(texto_rss == NULL)
    {
        printf("Erro!");
    }

    //tag inicio
    fprintf(texto_rss, "%s\n", "<html>");

    //titulo do canal
    fprintf(texto_rss, "%s\n%s %s %s\n%s\n", "<head>","<title>", canal.Titulo, "</title>", "</head>");

    //titulo do canal parte dois
    fprintf(texto_rss, "%s\n%s %s %s\n%s\n%s %s %s %s %s\n%s\n%s %s %s\n%s\n", "<body>", "<h1>",canal.Titulo, "</h1>","<br>", "<a href = \" ", canal.Link, "  \" > ", canal.Link, "</a>", "<br>", "<p>", canal.Descricao, "</p>", "<hr>");

    //criar um for para as noticias
    for(i=0; i<quant; i++)
    {
        fprintf(texto_rss, "%s%s%s\n%s%s%s\n%s%s%s%s%s\n%s%s%s\n%s", "<h2>", noticias[i].Titulo, "</h2>", "<p>", noticias[i].Descricao, "</p>", "<a href = \" ", noticias[i].Link, " \" > ", noticias[i].Link, "</a>", "<p>", noticias[i].Data, "</p>", "<hr>");
    }

    //tag fim
    fprintf(texto_rss, "%s\n%s", "</body>", "</html>");
}

int main()
{
    int tam_tag=0;

    //Sobre o Canal
    char tag_channel_abre[] = "<channel>";
    char tag_channel_fecha[] = "</channel>";
    int tag_channel_quant = 0;

    //Titulo do canal e da noticia
    char tag_title_abre[] = "<title>";
    char tag_title_fecha[] = "</title>";
    int tag_title_quant = 0;
    int *tag_title_abre_indices;
    int *tag_title_fecha_indices;

    //Descricao do canal e da noticia
    char tag_description_abre[] = "<description>";
    char tag_description_fecha[] = "</description>";
    int tag_description_quant = 0;
    int *tag_description_abre_indices;
    int *tag_description_fecha_indices;

    //Link do canal e da noticia
    char tag_link_abre[] = "<link>";
    char tag_link_fecha[] = "</link>";
    int tag_link_quant = 0;
    int *tag_link_abre_indices;
    int *tag_link_fecha_indices;

    //Sobre cada noticia (item)
    char tag_item_abre[] = "<item>";
    char tag_item_fecha[] = "</item>";
    int tag_item_quant = 0;
    int *tag_item_abre_indices;
    int *tag_item_fecha_indices;

    //Data de publicacao se disponivel
    char tag_pubDate_abre[] = "<pubDate>";
    char tag_pubDate_fecha[] = "</pubDate>";
    int tag_pubDate_quant = 0;
    int *tag_pubDate_abre_indices;
    int *tag_pubDate_fecha_indices;

    int i=0, tam_vetor=0, j=0, encontrou=0, k =0;
    char aux;

    FILE *texto;

    texto = fopen("arquivo.xml", "r+"); //abrindo arquivo para leitura e gravacao.

    if(texto == NULL)
    {
        fprintf(stderr, "Erro!\n");
    }

    while(fscanf(texto, "%c", &aux) != EOF)
    {
        i++;//tamanho do arquivo
    }

    char *vetor = malloc((i+1)*sizeof(char));//cria vetor

    rewind(texto);//volta ao inicio do arquivo

    i=0;

    while(fscanf(texto, "%c", &aux) != EOF) //passa os dados para o vetor
    {
        vetor[i] = aux;
        i++;
    }
    vetor[i] = '\0';

    rewind(texto);//volta ao inicio do arquivo

    fclose(texto);

    /********************CANAL********************/

    /********************Titulo********************/

    tag_title_quant = quantidade_tag(vetor, tag_title_abre);//quantidade de tags title

    //abre
    tag_title_abre_indices = encotra_tag(vetor,  tag_title_abre, tag_title_quant); //vetor com os indices das tags title abre

    //fecha
    tag_title_fecha_indices = encotra_tag(vetor,  tag_title_fecha, tag_title_quant); //vetor com os indices das tags title fecha

    //Titulo do canal
    tam_tag = strlen(tag_title_abre);

    j=0;

    for(i = (tag_title_abre_indices[0] + tam_tag); i <tag_title_fecha_indices[0]; i++)//copiar a frase para titulo
    {
        canal.Titulo[j]=vetor[i];
        j++;
    }


    /********************Descricao********************/

    tag_description_quant = quantidade_tag(vetor, tag_description_abre);

    //abre
    tag_description_abre_indices = encotra_tag(vetor, tag_description_abre, tag_description_quant); //vetor com os indices das tags description abre

    //fecha
    tag_description_fecha_indices = encotra_tag(vetor,  tag_description_fecha, tag_description_quant); //vetor com os indices das tags title fecha


    tam_tag = strlen(tag_description_abre);

    j=0;

    for(i = (tag_description_abre_indices[0] + tam_tag); i <tag_description_fecha_indices[0]; i++)//copiar a frase para titulo
    {
        canal.Descricao[j] = vetor[i];
        j++;
    }


    /********************Link********************/

    tag_link_quant = quantidade_tag(vetor, tag_link_abre);

    //abre
    tag_link_abre_indices = encotra_tag(vetor, tag_link_abre, tag_link_quant); //vetor com os indices das tags description abre

    //fecha
    tag_link_fecha_indices = encotra_tag(vetor,  tag_link_fecha, tag_link_quant); //vetor com os indices das tags title fecha


    tam_tag = strlen(tag_link_abre);

    j=0;

    for(i = (tag_link_abre_indices[0] + tam_tag); i <tag_link_fecha_indices[0]; i++)//copiar a frase para titulo
    {
        canal.Link[j] = vetor[i];
        j++;
    }


    /********************NOTICIAS********************/

    tag_item_quant = quantidade_tag(vetor, tag_item_abre);

    //abre
    tag_item_abre_indices = encotra_tag(vetor, tag_item_abre, tag_item_quant); //vetor com os indices das tags title abre

    //fecha
    tag_item_fecha_indices = encotra_tag(vetor, tag_item_fecha, tag_item_quant); //vetor com os indices das tags title fecha


    /********************Titulo********************/

    tag_title_quant = quantidade_tag(vetor, tag_title_abre);//quantidade de tags title

    //abre
    tag_title_abre_indices = encotra_tag(vetor,  tag_title_abre, tag_title_quant); //vetor com os indices das tags title abre

    //fecha
    tag_title_fecha_indices = encotra_tag(vetor,  tag_title_fecha, tag_title_quant); //vetor com os indices das tags title fecha

    tam_tag = strlen(tag_title_abre);

    k=0;
    i=0;
    j=0;
    int r=0;
    int y=0;
    int h=0;
    int z=0;
    int w=0;


    while(i < tag_item_fecha_indices[k])
    {
        i = tag_item_abre_indices[k];

        y=0;
        for(  j = tag_title_abre_indices[y]; j < tag_title_fecha_indices[y]; j++)
        {
            if(tag_title_abre_indices[y] > tag_item_abre_indices[k] && tag_title_fecha_indices[y] < tag_item_fecha_indices[k])
            {
                z=0;
                for(h = tag_title_abre_indices[y] + tam_tag; h <tag_title_fecha_indices[y]; h++)//copiar a frase para titulo
                {
                    noticias[w].Titulo[z] = vetor[h];
                    z++;
                }
                w++;
            }
            y++;
        }
        k++;
    }

    /********************NOTICIAS - Descricao********************/

    tag_item_quant = quantidade_tag(vetor, tag_item_abre);

    //abre
    tag_item_abre_indices = encotra_tag(vetor, tag_item_abre, tag_item_quant); //vetor com os indices das tags title abre

    //fecha
    tag_item_fecha_indices = encotra_tag(vetor, tag_item_fecha, tag_item_quant); //vetor com os indices das tags title fecha


    /********************Descricao********************/

    tag_description_quant = quantidade_tag(vetor, tag_description_abre);//quantidade de tags title

    //abre
    tag_description_abre_indices = encotra_tag(vetor,  tag_description_abre, tag_description_quant); //vetor com os indices das tags title abre

    //fecha
    tag_description_fecha_indices = encotra_tag(vetor,  tag_description_fecha, tag_description_quant); //vetor com os indices das tags title fecha

    tam_tag = strlen(tag_description_abre);

    j=0;
    r=0;
    y=0;
    k=0;
    h=0;
    z=0;
    w=0;
    i=0;
    j=0;

    while(i < tag_item_fecha_indices[k])
    {
        i = tag_item_abre_indices[k];

        y=0;

        for(j = tag_description_abre_indices[y]; j < tag_description_fecha_indices[y]; j++)
        {
            if(tag_description_abre_indices[y] > tag_item_abre_indices[k] && tag_description_fecha_indices[y] < tag_item_fecha_indices[k])
            {
                z=0;

                for(h = tag_description_abre_indices[y] + tam_tag; h <tag_description_fecha_indices[y]; h++)//copiar a frase para titulo
                {
                    noticias[w].Descricao[z] = vetor[h];
                    z++;
                }
                w++;
            }
            y++;
        }
        k++;
    }


    /********************NOTICIAS - Link********************/

    tag_item_quant = quantidade_tag(vetor, tag_item_abre);

    //abre
    tag_item_abre_indices = encotra_tag(vetor, tag_item_abre, tag_item_quant); //vetor com os indices das tags title abre

    //fecha
    tag_item_fecha_indices = encotra_tag(vetor, tag_item_fecha, tag_item_quant); //vetor com os indices das tags title fecha


    /********************Link********************/

    tag_link_quant = quantidade_tag(vetor, tag_link_abre);//quantidade de tags title

    //abre
    tag_link_abre_indices = encotra_tag(vetor,  tag_link_abre, tag_link_quant); //vetor com os indices das tags title abre

    //fecha
    tag_link_fecha_indices = encotra_tag(vetor,  tag_link_fecha, tag_link_quant); //vetor com os indices das tags title fecha

    tam_tag = strlen(tag_link_abre);

    j=0;
    r=0;
    y=0;
    k=0;
    h=0;
    z=0;
    w=0;
    i=0;
    j=0;

    while(i < tag_item_fecha_indices[k])
    {
        i = tag_item_abre_indices[k];

        y=0;

        for(j = tag_link_abre_indices[y]; j < tag_link_fecha_indices[y]; j++)
        {
            if(tag_link_abre_indices[y] > tag_item_abre_indices[k] && tag_link_fecha_indices[y] < tag_item_fecha_indices[k])
            {
                z=0;

                for(h = tag_link_abre_indices[y] + tam_tag; h <tag_link_fecha_indices[y]; h++)//copiar a frase para titulo
                {
                    noticias[w].Link[z] = vetor[h];
                    z++;
                }
                w++;
            }
            y++;
        }
        k++;
    }


    /********************NOTICIAS - Data********************/

    tag_item_quant = quantidade_tag(vetor, tag_item_abre);

    //abre
    tag_item_abre_indices = encotra_tag(vetor, tag_item_abre, tag_item_quant); //vetor com os indices das tags title abre

    //fecha
    tag_item_fecha_indices = encotra_tag(vetor, tag_item_fecha, tag_item_quant); //vetor com os indices das tags title fecha


    /********************Data********************/

    tag_pubDate_quant = quantidade_tag(vetor, tag_pubDate_abre);//quantidade de tags title

    //abre
    tag_pubDate_abre_indices = encotra_tag(vetor,  tag_pubDate_abre, tag_pubDate_quant); //vetor com os indices das tags title abre

    //fecha
    tag_pubDate_fecha_indices = encotra_tag(vetor, tag_pubDate_fecha, tag_pubDate_quant); //vetor com os indices das tags title fecha

    tam_tag = strlen(tag_pubDate_abre);

    j=0;
    r=0;
    y=0;
    k=0;
    h=0;
    z=0;
    w=0;
    i=0;
    j=0;

    while(i < tag_item_fecha_indices[k])
    {
        i = tag_item_abre_indices[k];

        y=0;

        for(j = tag_pubDate_abre_indices[y]; j < tag_pubDate_fecha_indices[y]; j++)
        {
            if(tag_pubDate_abre_indices[y] > tag_item_abre_indices[k] && tag_pubDate_fecha_indices[y] < tag_item_fecha_indices[k])
            {
                z=0;

                for(h = tag_pubDate_abre_indices[y] + tam_tag; h <tag_pubDate_fecha_indices[y]; h++)//copiar a frase para titulo
                {
                    noticias[w].Data[z] = vetor[h];
                    z++;
                }
                w++;
            }
            y++;
        }
        k++;
    }


    /********************Arquivo HTML********************/

    int quant = quantidade_tag(vetor, tag_item_abre); //quantidade de noticias

    arquivo_html(canal, noticias, quant);

    return 0;
}
