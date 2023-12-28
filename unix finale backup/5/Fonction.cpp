


 //to do etape 1.2// faire renvoyer a client et verif si le mot de passe et juste je dois probablement faire un while
                      if(strcmp(m.data1,"1")==0)//cas ou ils veut se login// en gros 0= déja crée 1=il veut crrée un compte
                      {
                        fprintf(stderr,"(Creation de compte)\n");
                        if(estPresent(m.data2)>0)//verifie sI LE PSEUDO EXISTE DÉJA
                        {
                          fprintf(stderr,"(Ton pseudo est déja prit\n");
                        //je remplis la réponse wallah
                          strcpy(reponse.data1,"KO");
                          strcpy(reponse.texte,"Nom déja prit");
                          reponse.type=m.expediteur;
                        reponse.expediteur=1;//probablement car serveur et donc la norme
                        reponse.requete=LOGIN;

                        msgsnd(idQ,&reponse,sizeof(MESSAGE)-sizeof(long),0); //en gros j'envoie au client nom déja prit
                        kill(reponse.type,SIGUSR1);// Pour envoyer un signal 


                      }

                        else//cas ou le nom existe pas on le crée (en gros tu te crée un compte)
                        {
                          fprintf(stderr,"(le pseudo existe pas ben je te le crée)\n");
                          if(strcmp(m.texte,"")!=0)
                          {
                            //Update pour les nom dans son machin avec les noms
                            fprintf(stderr,"(Update des nom dans la liste Serveur)\n");
                            i=0;
                            while(tab->connexions[i].pidFenetre != m.expediteur && i<6)//on boucle jusqu'a il ezreouve le pid ou qu'il depasse 6 itération
                            {
                              i++;
                            }
                            if(i<6)
                            {
                              strcpy(tab->connexions[i].nom,m.data2); 
                            }
                           ajouteUtilisateur(m.data2,m.texte);// en gros nom -mdp ajouter dans un fichier
                           //préparation de la réponse//
                           strcpy(reponse.data1, "OK");
                           strcpy(reponse.texte, "Nom créé");
                           reponse.type = m.expediteur;
                           reponse.expediteur = 1;//probablement car serveur et donc la norme
                           reponse.requete=LOGIN;

                           msgsnd(idQ, &reponse, sizeof(MESSAGE) - sizeof(long), 0);//en gros j'envoie au client l'info que ca a été crée
                           kill(reponse.type,SIGUSR1);// Pour envoyer un signal


                          //////////////2.a//////////////////////////
                          //Il informet les autres clients que

                          //Donc en gros on boucle jusqu'a trouver un tableau avec une valeur autre que 0 si on le trouve on prépare la réponse et on envoie signal aux utilisateurs qui étaient la avant pour informer que un nouvel utilisateur s'est connecter
                          MESSAGE UpdateUserCo;//variable temps
                          for (int i = 0; i < 6; i++)
                          {
                             if(tab->connexions[i].pidFenetre!=0 && strcmp(tab->connexions[i].nom,m.data2)!=0 &&strcmp(tab->connexions[i].nom,"")!=0)
                             {
                                UpdateUserCo.type = tab->connexions[i].pidFenetre;
                                UpdateUserCo.requete=ADD_USER;
                                UpdateUserCo.expediteur=1;//déja fait 
                                strcpy(UpdateUserCo.data1,m.data2);
                                msgsnd(idQ, &UpdateUserCo, sizeof(MESSAGE) - sizeof(long), 0);
                                
                                fprintf(stderr,"(Le pid %d vers updated avec un nouveau utilisateur  %s)\n",UpdateUserCo.type,UpdateUserCo.data1);
                                kill(UpdateUserCo.type,SIGUSR1);
                                fprintf(stderr,"(Envoie faite avec succés du data1 %s)\n",UpdateUserCo.data1);

                             }
                          }

                          MESSAGE NouveauUserUpdater;//variable temps
                          for (int i = 0; i < 6; i++)//j'ai trop la flemme de commenté mais c'est pour que  le nv recoive les infos des iencli
                          {
                             if(tab->connexions[i].pidFenetre!=0 && strcmp(tab->connexions[i].nom,"")!=0 && strcmp(tab->connexions[i].nom,m.data2)!=0)
                             {
                                NouveauUserUpdater.type = m.expediteur;
                                NouveauUserUpdater.requete=ADD_USER;
                                NouveauUserUpdater.expediteur=1;//déja fait 
                                strcpy(NouveauUserUpdater.data1,tab->connexions[i].nom);
                                msgsnd(idQ, &NouveauUserUpdater, sizeof(MESSAGE) - sizeof(long), 0);
                                
                                fprintf(stderr,"(Le pid %d vers updated avec un nouveau utilisateur  %s)\n",NouveauUserUpdater.type,NouveauUserUpdater.data1);
                                kill(NouveauUserUpdater.type,SIGUSR1);
                                fprintf(stderr,"(Envoie faite avec succés du data1 %s)\n",NouveauUserUpdater.data1);

                             }
                          }

                          //////////////////////////////////////////////////////////////////////////////////////////////////////////:/

                          //en gros update dans mysql un nouveau utilisateur
                          ///////////////////////5////////////////////////////

                          sprintf(requete,"insert into UNIX_FINAL values (NULL,'%s','---','---');",m.data2);//j'ai un core dump a cause de ca (90% DU TEMPS CA MARCHE ) ~~ GENRE CA INSERE BIEN MEME QUAND CA CORE DUMP

                          mysql_query(connexion,requete);
                          
                          fprintf(stderr,"Insertion OK.\n");


                          // Déconnexion de la base de données
                          // mysql_close(connexion);

                          /////////////////////////////////////////////////
                          }
                          else
                          {
                            fprintf(stderr,"Mot de passe Invalide vide \n");
                            strcpy(reponse.data1,"KO");
                            strcpy(reponse.texte,"Mot de passe Invalide vide");
                            reponse.type=m.expediteur;
                            reponse.expediteur=1;//probablement car serveur et donc la norme
                            reponse.requete=LOGIN;

                            msgsnd(idQ,&reponse,sizeof(MESSAGE)-sizeof(long),0);//en gros j'envoie au client l'info que ca a été crée
                            kill(reponse.type,SIGUSR1);// Pour envoyer un signal
                          }
                         
                       }



                      }//cas ou on veut se log in avec un compte
                      else
                      {
                        fprintf(stderr,"(Login de compte)\n");//pourquoi toujours ici malgré le fait que la valeur soit 0 ou 1 //to do list prévoir le cas ou le nom apparait deux fois
                        if(estPresent(m.data2)>0)//si le nom est présent
                        {
                          if(verifieMotDePasse(estPresent(m.data2),m.texte)==1)//check le password //valide password ou non 
                          {
                            fprintf(stderr,"(Mot de passe correct)\n");

                            //Update pour les nom dans son machin avec les noms
                            fprintf(stderr,"(Update des nom dans la liste Serveur)\n");// a déplacer ca se fait aprés la r"alisation du case 
                            i=0;
                             while(tab->connexions[i].pidFenetre != m.expediteur && i<6)//on boucle jusqu'a il ezreouve le pid ou qu'il depasse 6 itération
                             {
                              i++;
                            }
                            if(i<6)
                            {

                              strcpy(tab->connexions[i].nom,m.data2);

                            }

                          //préparation de la réponse//
                            strcpy(reponse.data1,"OK");
                            strcpy(reponse.texte,"Rebonjour utilisateur");
                            reponse.type=m.expediteur;
                          reponse.expediteur=1;//probablement car serveur et donc la norme
                          reponse.requete=LOGIN;

                          msgsnd(idQ,&reponse,sizeof(MESSAGE)-sizeof(long),0);//en gros j'envoie au client l'info que ca a été crée

                          kill(reponse.type,SIGUSR1);// Pour envoyer un signal

                          //////////////2.a//////////////////////////
                          //Il informet les autres clients que

                          //Donc en gros on boucle jusqu'a trouver un tableau avec une valeur autre que 0 si on le trouve on prépare la réponse et on envoie signal aux utilisateurs qui étaient la avant pour informer que un nouvel utilisateur s'est connecter
                          MESSAGE UpdateUserCo;//variable temps
                          for (int i = 0; i < 6; i++)
                          {
                             if(tab->connexions[i].pidFenetre!=0 && strcmp(tab->connexions[i].nom,m.data2)!=0 &&strcmp(tab->connexions[i].nom,"")!=0)
                             {
                                UpdateUserCo.type = tab->connexions[i].pidFenetre;
                                UpdateUserCo.requete=ADD_USER;
                                UpdateUserCo.expediteur=1;//déja fait 
                                strcpy(UpdateUserCo.data1,m.data2);
                                msgsnd(idQ, &UpdateUserCo, sizeof(MESSAGE) - sizeof(long), 0);
                                
                                fprintf(stderr,"(Le pid %d vers updated avec un nouveau utilisateur  %s)\n",UpdateUserCo.type,UpdateUserCo.data1);
                                kill(UpdateUserCo.type,SIGUSR1);
                                fprintf(stderr,"(Envoie faite avec succés du data1 %s)\n",UpdateUserCo.data1);

                             }
                          }

                          MESSAGE NouveauUserUpdater;//variable temps
                          for (int i = 0; i < 6; i++)//j'ai trop la flemme de commenté mais c'est pour que  le nv recoive les infos des iencli
                          {
                             if(tab->connexions[i].pidFenetre!=0 && strcmp(tab->connexions[i].nom,"")!=0 && strcmp(tab->connexions[i].nom,m.data2)!=0)
                             {
                                NouveauUserUpdater.type = m.expediteur;
                                NouveauUserUpdater.requete=ADD_USER;
                                NouveauUserUpdater.expediteur=1;//déja fait 
                                strcpy(NouveauUserUpdater.data1,tab->connexions[i].nom);
                                msgsnd(idQ, &NouveauUserUpdater, sizeof(MESSAGE) - sizeof(long), 0);
                                
                                fprintf(stderr,"(Le pid %d vers updated avec un nouveau utilisateur  %s)\n",NouveauUserUpdater.type,NouveauUserUpdater.data1);
                                kill(NouveauUserUpdater.type,SIGUSR1);
                                fprintf(stderr,"(Envoie faite avec succés du data1 %s)\n",NouveauUserUpdater.data1);

                             }
                          }

                          //////////////////////////////////////////////////////////////////////////////////////////////////////////:/
                        }
                          else//si pas le bon mdp
                          {
                            fprintf(stderr,"(Mot de passe incorrect)\n");
                            strcpy(reponse.data1,"KO");
                            strcpy(reponse.texte,"Mot de passe incorrect");
                            reponse.type=m.expediteur;
                          reponse.expediteur=1;//probablement car serveur et donc la norme
                          reponse.requete=LOGIN;

                          msgsnd(idQ,&reponse,sizeof(MESSAGE)-sizeof(long),0);//en gros j'envoie au client l'info que ca a été crée
                          kill(reponse.type,SIGUSR1);// Pour envoyer un signal

                        }
                      }
                        else//cas ou le nom existe pas
                        {
                          fprintf(stderr,"(Ton pseudo n'hésite pas tu as fait une Eric)\n");
                          strcpy(reponse.data1,"KO");
                          strcpy(reponse.texte,"Nom Inconnu");
                          reponse.type=m.expediteur;
                          reponse.expediteur=1;//probablement car serveur et donc la norme
                          reponse.requete=LOGIN;

                          msgsnd(idQ,&reponse,sizeof(MESSAGE)-sizeof(long),0);//en gros j'envoie au client l'info que ca a été crée
                          kill(reponse.type,SIGUSR1);// Pour envoyer un signal

                        }
                      }
