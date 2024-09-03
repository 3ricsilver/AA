#ifndef IMAGENG_H
#define IMAGENG_H
#include "Dimension.h"
#include "Image.h"

class ImageNG : public Image
{

  private:

  int matrice[L_MAX][H_MAX];

  public:

  //constructeur
  ImageNG();                                            
  ~ImageNG();                                           
  ImageNG(int id, const char* N);                       
  ImageNG(const ImageNG& image1);                       
  ImageNG(int id, const char* N, const Dimension& dim); 
  ImageNG(const char* fichier);                         

  //get set
  void setPixel(int x, int y, int val);
  void setBackground(int val);
  int getPixel(int x, int y) const;

  int getLuminance() const;
  int getMinimum() const;
  int getMaximum() const;
  float getContraste() const;

  //methode
  void Affiche() const;
  void Dessine() const;
  void importFromFile(const char* fichier);
  void exportToFile(const char* fichier, const char* format);

  //surcharge
  ImageNG& operator=(const ImageNG& image);
  ImageNG operator+(int val);
  ImageNG operator-(int val);
  ImageNG operator++(); // pré
  ImageNG operator++(int sertARien); // post
  ImageNG operator--(); // pré
  ImageNG operator--(int sertARien); // post
  ImageNG operator-(const ImageNG& image);
  bool operator<(const ImageNG& image) const;
  bool operator>(const ImageNG& image) const;
  bool operator==(const ImageNG& image) const;

  friend std::ostream& operator<<(std::ostream& s,const ImageNG& image);
  friend ImageNG operator+(int val, ImageNG image);


};

#endif