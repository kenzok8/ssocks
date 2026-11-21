/* bor-util.c : Boite a Outil Reseau
 *
 * Edouard.Thiel@lif.univ-mrs.fr - 22/01/2009 - V 2.0
 *
 * This program is free software under the terms of the
 * GNU Lesser General Public License (LGPL) version 2.1.
*/

#include "bor-util.h"


/* Affiche le message de perror en conservant la valeur de errno.
*/
void bor_perror (const char *funcname)
{
    int e = errno;
    perror (funcname);
    errno = e;
}


/*  Place le handler de signal void h(int) pour le signal sig avec sigaction().
    Le signal est automatiquement masque pendant sa delivrance.
    Si options = 0,
      - les appels bloquants sont interrompus avec retour -1 et errno = EINTR.
      - le handler est rearme automatiquement apres chaque delivrance de signal.
    si options est une combinaison bit a bit de
      - SA_RESTART : les appels bloquants sont silencieusement repris.
      - SA_RESETHAND : le handler n'est pas rearme.
    Renvoie le resultat de sigaction. Verbeux.
*/
#ifndef _WIN32
int bor_signal (int sig, void (*h)(int), int options)
{
    int r;
    struct sigaction s;
    s.sa_handler = h;
    sigemptyset (&s.sa_mask);
    s.sa_flags = options;
    r = sigaction (sig, &s, NULL);
    if (r < 0) bor_perror (__func__);
    return r;
}
#endif


/* Attachement d'une socket de domaine AF_INET a une adresse sockaddr_in
   Renvoie le resultat de bind(). Verbeux.
*/
int bor_bind_in (int soc, struct sockaddr_in *adr)
{
    int r = bind (soc, (struct sockaddr *) adr, sizeof(struct sockaddr_in));
    if (r < 0) bor_perror (__func__);
    return r;
}


/* Connexion a un serveur TCP/IP
   Renvoie le resultat de connect. Verbeux.
*/
int bor_connect_in (int soc, struct sockaddr_in *adr)
{
    int r = connect (soc, (struct sockaddr *) adr, sizeof(struct sockaddr_in));
    if (r < 0) bor_perror (__func__);
    return r;
}


/* Accepte une connexion en attente.
   Renvoie le resultat de accept. Verbeux.
*/
int bor_accept_in (int soc, struct sockaddr_in *adr)
{
    socklen_t adrlen = sizeof(struct sockaddr_in);
    int r = accept (soc, (struct sockaddr *) adr, &adrlen);
    if (r < 0) bor_perror (__func__);
    return r;
}


/* Recuperation de l'adresse reelle et du port sous forme Network
   Renvoie le resultat de getsockname. Verbeux.
*/
int bor_getsockname_in (int soc, struct sockaddr_in *adr)
{
    socklen_t adrlen = sizeof(struct sockaddr_in);
    int r = getsockname (soc, (struct sockaddr *) adr, &adrlen);
    if (r < 0) bor_perror (__func__);
    return r;
}


/* Renvoie l'adresse d'une chaine en memoire statique contenant l'adresse IPv4
 * sous la forme "a.b.c.d:port", de facon a pouvoir l'afficher. Silencieux.
*/
char *bor_adrtoa_in (struct sockaddr_in *adr)
{
    static char s[32];
    sprintf (s, "%s:%d", inet_ntoa(adr->sin_addr), ntohs(adr->sin_port));
    return s;
}

