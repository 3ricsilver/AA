// m.exp m.data2 -> username

strcpy(reponse.data1, m.data2);

for (auto user : tab->connexions){
	if(user.pidFenetre){
		reponse.type = .pidFenetre;
		msgsnd(idQ, &reponser, sizeof(MESSAGE) - sizeof(long), 0);
		kill(.pidFenetre, SIGUSR1);
	}
}

strcpy(reponse.data1, m.data2);

for (int i = 0; i < 6; i++)
{
	if(tab->connexion[i].pidFenetre)
	{
		reponse.type = tab->connexion[i].pidFenetre;
		msgsnd(idQ, &reponser, sizeof(MESSAGE) - sizeof(long), 0);
		kill(tab->connexion[i].pidFenetre, SIGUSR1);
	}
}