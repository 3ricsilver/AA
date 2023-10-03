#ifndef IMAGENG_H //si pas definit on le definit sinon osef car on va boucler
#define IMAGENG_H

class ImageNG
{
	private:
		int id;
  		char *nom;
	public:
		ImageNG();
		ImageNG(int i,const char *n);
		ImageNG(const ImageNG& i);
		~ImageNG();
		void setId(int val);
		void setNom(const char *n);
		int getId()const;
		const char *getNom() const;
		void Affiche() const;
};

#endif
