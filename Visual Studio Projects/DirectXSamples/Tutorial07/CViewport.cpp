#include "CViewport.h"

//! An \fn.
	/*!
	  init for class CViewport, init data with m_Viewport only in D3D11
	  \param _C_DEVICE_DESC an C_Viewport_DESC.
	*/
int CViewport::init(C_Viewport_DESC & _C_DEVICE_DESC)
{
#if defined(D3D11)

	m_Viewport = _C_DEVICE_DESC;
	ZeroMemory(&data, sizeof(data));
	/*m_Viewport.vp.Width = m_Viewport.Width;
	m_Viewport.vp.Height = m_Viewport.Height;
	m_Viewport.vp.MinDepth = m_Viewport.MinDepth;
	m_Viewport.vp.MaxDepth = m_Viewport.MaxDepth;
	m_Viewport.vp.TopLeftX = m_Viewport.TopLeftX;
	m_Viewport.vp.TopLeftY = m_Viewport.TopLeftY;*/
	data.Height = m_Viewport.Height;
	data.Width = m_Viewport.Width;
	data.MinDepth = m_Viewport.MinDepth;
	data.MaxDepth = m_Viewport.MaxDepth;
	data.TopLeftX = m_Viewport.TopLeftX;
	data.TopLeftY = m_Viewport.TopLeftY;
	
#else 

#endif
	return 0;
}

//! An \fn.
	/*!
	  update for the class CViewport
	*/
void CViewport::update()
{
}

//! An \fn.
	/*!
	  detroy for the class CViewport
	*/
void CViewport::detroy()
{
}

//! An \fn.
	/*!
	  render for the class CViewport
	*/
void CViewport::render()
{
}
