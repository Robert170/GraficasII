#pragma once

#include "Define.h"
#include "CDeviceContext.h"
#include "CInputLayer.h"
#include "CVertexShader.h"
#include "CPixelShader.h"
#include "CTargetView.h"
#include "CDepthStencilVoew.h"
#include "CBuffer.h"
#include "CCamera.h"
#include "CViewport.h"
#include "CSampleState.h"
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include "CTexture2D.h"
#include "CRenderTarget.h"
#include "CDepthStencilVoew.h"
#include "CSceneManager.h"
#include "CViewport.h"



struct PASSE_DIRECTX_STRUCT
{

	CDeviceContext* DevConTextStruct;
	CDevice* DevStruc;
	unsigned int RenTarViewCount;
	C_Texture2D_DESC TexStruct;

#ifdef D3D11
	D3D11_RASTERIZER_DESC RDStateStruct;
#endif
	//CVertexShader* VertShader;
	//CPixelShader* PixShader;

	//CViewport* ViewPort;

	//CBuffer * p_BoneBuffer;
	//std::vector<CTargetView*> VecRefRenderTarget;
	//std::vector< CSceneManager>* VecRefModels;

	//CDeviceContext* DevConTextStruct;
	//CDevice* DevStruc;
	//
	//CInputLayer* IntLay;

	//CVertexShader* VertShader;
	//CPixelShader* PixShader;

	//CViewport* ViewPort;

	////CBuffer * p_BoneBuffer;
	//std::vector<CTargetView*> VecRefRenderTarget;
	//std::vector< CSceneManager>* VecRefModels;

};


class CPase
{
public:
	CPase();
	//PASSE_DIRECTX_STRUCT m_PaseDirectx;
	//PASSE_OPENGL_STRUCT m_PaseOpenGL;

	//CBuffer * m_pCBB;

	CInputLayer m_IntLay;

	CVertexShader m_VertShader;
	CPixelShader m_PixShader;

	CDeviceContext* m_DevCont;

	CViewport m_ViewPort;

#ifdef D3D11
	ID3D11RasterizerState* m_RasState;
	//referenci a objetos que vamos a utilizar
	std::vector<ID3D11RenderTargetView*> m_vRenTarView;

	//para las texturas
	std::vector<CTexture2D*> m_vTexts;

	//para render targert de otros pases
	std::vector<ID3D11ShaderResourceView*> m_vShadResView;

	std::vector<ID3D11ShaderResourceView*> m_vImGuiPase;

	int initDX(PASSE_DIRECTX_STRUCT& _C_Pase_DESC);
#endif

	
	void detroy();
	void render();


#ifdef D3D11

	void SetRenderTarget(CDepthStencilView* DevStV);
	void SetShader();

	//limpia la pantalla
	void Clear(float ClearColor[4], CDepthStencilView* DevStV);

	void Draw(CSceneManager* ScManger);
	void SetPass(CDepthStencilView* DevStV);
	void FillShaderResource(CDevice* Dev, CTexture2D* Text);
#endif
	
};

