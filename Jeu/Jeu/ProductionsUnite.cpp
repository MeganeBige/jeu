#include "ProductionsUnite.h"

ProductionsUnite::ProductionsUnite(int _x, int _y, string _nom, string _desc, ...) : Batiment(_x, _y, _nom, _desc, Ressource::AUCUNE, 0)
{
	va_list pa;

	va_start(pa, _desc);
	Unite* val = va_arg(pa, Unite*);
	while(val != NULL)
	{
		unites[val->getNom()] = val;
		val = va_arg(pa, Unite*);
	}
	va_end(pa);
}

ProductionsUnite::~ProductionsUnite()
{

}
