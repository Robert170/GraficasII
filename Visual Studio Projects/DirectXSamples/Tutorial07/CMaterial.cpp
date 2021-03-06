#include "CMaterial.h"

// !A \fn.
/*!
  function for construc the class.
*/
CMaterial::CMaterial()
{
	m_TexNorm = nullptr;
	m_TexDif = nullptr;
	m_TexSpecular = nullptr;
}

// !A \fn.
/*!
  function for destroy the class.
*/
CMaterial::~CMaterial()
{
}

// !A \fn.
/*!
  function for texture difuse.
*/
void CMaterial::Shutdown()
{
#if defined(D3D11)
	if (m_TexDif)
	{
		m_TexDif->Release();
	}
	if (m_TexNorm)
	{
		m_TexNorm->Release();
	}
	if (m_TexSpecular)
	{
		m_TexSpecular->Release();
	}
		

#endif // D3D11
	
}
