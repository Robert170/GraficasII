#include "CPase.h"

CPase::CPase()
{
	m_DevCont = nullptr;
}

int CPase::initDX(PASSE_DIRECTX_STRUCT & _C_Pase_DESC, int MipLevel)
{
#if defined(D3D11)

	m_DevCont = _C_Pase_DESC.DevConTextStruct;
	HRESULT hr;

	for (int i = 0; i < _C_Pase_DESC.RenTarViewCount; i++)
	{
		CTexture2D* TexT2D = new CTexture2D();

		TexT2D->init(_C_Pase_DESC.TexStruct);

		hr = _C_Pase_DESC.DevStruc->g_pd3dDevice->CreateTexture2D(&TexT2D->Tex_Des, NULL, &TexT2D->m_pTexture);

		if (FAILED(hr))
		{
			return -1;
		}
			
		m_vTexts.push_back(TexT2D);

		D3D11_RENDER_TARGET_VIEW_DESC RenTaViewDESC;
		ZeroMemory(&RenTaViewDESC, sizeof(RenTaViewDESC));
		RenTaViewDESC.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
		RenTaViewDESC.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		RenTaViewDESC.Texture2D.MipSlice = 0;

		ID3D11RenderTargetView* RenT;

		hr = _C_Pase_DESC.DevStruc->g_pd3dDevice->CreateRenderTargetView(TexT2D->m_pTexture, &RenTaViewDESC, &RenT);

		if (FAILED(hr))
		{
			return -1;
		}

		m_vRenTarView.push_back(RenT);

		D3D11_SHADER_RESOURCE_VIEW_DESC ShReView;

		ShReView.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
		ShReView.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		ShReView.Texture2D.MostDetailedMip = 0;
		ShReView.Texture2D.MipLevels = MipLevel;

		ID3D11ShaderResourceView* Srv;

		hr = _C_Pase_DESC.DevStruc->g_pd3dDevice->CreateShaderResourceView(TexT2D->m_pTexture, &ShReView, &Srv);

		if (FAILED(hr))
		{
			return -1;
		}
		m_vImGuiPase.push_back(Srv);

		//_C_Pase_DESC.DevStruc->g_pd3dDevice->CreateRasterizerState(&_C_Pase_DESC.RDStateStruct, &m_RasState);	
	}
#else 

#endif
	return 0;
}


void CPase::detroy()
{
}

void CPase::render()
{
}

void CPase::SetRenderTarget(CDepthStencilView* DevStV)
{
#ifdef D3D11
	if (DevStV)
	{
		m_DevCont->g_pImmediateContext->OMSetRenderTargets(m_vRenTarView.size(), &m_vRenTarView[0], DevStV->g_pDepthStencilView);
	}
	else
	{
		m_DevCont->g_pImmediateContext->OMSetRenderTargets(m_vRenTarView.size(), &m_vRenTarView[0], NULL);
	}
	
	//m_DevCont->g_pImmediateContext->RSSetState(m_RasState);
#endif // D3D1
}

void CPase::SetShader()
{
#ifdef D3D11
	m_DevCont->g_pImmediateContext->IASetInputLayout(m_IntLay.g_pVertexLayout);
	m_DevCont->g_pImmediateContext->VSSetShader(m_VertShader.g_pVertexShader, NULL, 0);
	m_DevCont->g_pImmediateContext->PSSetShader(m_PixShader.g_pPixelShader, NULL, 0);
#endif // D3D11
}

void CPase::Clear(float ClearColor[4], CDepthStencilView* DevStV)
{
	if (m_DevCont!=nullptr)
	{
		for (int i = 0; i < m_vRenTarView.size(); i++)
		{
			m_DevCont->g_pImmediateContext->ClearRenderTargetView(m_vRenTarView[i], ClearColor);
		}
		m_DevCont->g_pImmediateContext->ClearDepthStencilView(DevStV->g_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	}
}

void CPase::Draw(CSceneManager* ScManger)
{
	for (int i = 0; i < ScManger->m_MeshInScene.size(); i++)
	{
		UINT Stride = sizeof(SimpleVertex);
		UINT Offset = 0;

		m_DevCont->g_pImmediateContext->IASetVertexBuffers(0, 1, &ScManger->m_MeshInScene[i]->m_VertexBuffer->P_Buffer, &Stride, &Offset);
		m_DevCont->g_pImmediateContext->IASetIndexBuffer(ScManger->m_MeshInScene[i]->m_Index->P_Buffer, DXGI_FORMAT_R16_UINT, 0);
		m_DevCont->g_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		if (ScManger->m_MeshInScene[i]->m_Materials->m_TexDif!=nullptr)
		{

			m_DevCont->g_pImmediateContext->PSSetShaderResources(0, 1, &ScManger->m_MeshInScene[i]->m_Materials->m_TexDif);
			if (ScManger->m_MeshInScene[i]->m_Materials->m_TexNorm !=nullptr && ScManger->m_MeshInScene[i]->m_Materials->m_TexSpecular != nullptr)
			{
				m_DevCont->g_pImmediateContext->PSSetShaderResources(1, 1, &ScManger->m_MeshInScene[i]->m_Materials->m_TexNorm);
				m_DevCont->g_pImmediateContext->PSSetShaderResources(2, 1, &ScManger->m_MeshInScene[i]->m_Materials->m_TexSpecular);
			}

		}
		else
		{
			for (int i = 0; i < m_vShadResView.size(); i++)
			{
				m_DevCont->g_pImmediateContext->PSSetShaderResources(i, 1, &m_vShadResView[i]);
			}
		}
		m_DevCont->g_pImmediateContext->DrawIndexed(ScManger->m_MeshInScene[i]->m_IndexNum, 0, 0);
	}
	
 
}

void CPase::SetPass(CDepthStencilView* DevStV)
{
	SetRenderTarget(DevStV);
	SetShader();
}

void CPase::FillShaderResource(CDevice* Dev, CTexture2D* Text)
{

	HRESULT hr;
	D3D11_SHADER_RESOURCE_VIEW_DESC ShadDesc;
	ZeroMemory(&ShadDesc, sizeof(ShadDesc));

	ShadDesc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
	ShadDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	ShadDesc.Texture2D.MostDetailedMip = 0;
	ShadDesc.Texture2D.MipLevels = 1;

	ID3D11ShaderResourceView* SRV;

	hr = Dev->g_pd3dDevice->CreateShaderResourceView(Text->m_pTexture, &ShadDesc, &SRV);

	if (FAILED(hr))
	{
		return;
	}

	m_vShadResView.push_back(SRV);
}

void CPase::FrTexture(CTexture2D* Text, CDevice* Dev)
{
	HRESULT hr;
	D3D11_RENDER_TARGET_VIEW_DESC RenTarViewDesc;
	ZeroMemory(&RenTarViewDesc, sizeof(RenTarViewDesc));
	RenTarViewDesc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
	RenTarViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	RenTarViewDesc.Texture2D.MipSlice = 0;

	ID3D11RenderTargetView* RenTarView;
	hr = Dev->g_pd3dDevice->CreateRenderTargetView(Text->m_pTexture, &RenTarViewDesc, &RenTarView);
	if (FAILED(hr))
	{
		return;
	}

	m_vRenTarView.push_back(RenTarView);

	D3D11_SHADER_RESOURCE_VIEW_DESC ShaResViewDesc;
	ShaResViewDesc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
	ShaResViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	ShaResViewDesc.Texture2D.MostDetailedMip = 0;
	ShaResViewDesc.Texture2D.MipLevels = 1;

	ID3D11ShaderResourceView* ShaResView;

	hr = Dev->g_pd3dDevice->CreateShaderResourceView(Text->m_pTexture, &ShaResViewDesc, &ShaResView);

	if (FAILED(hr))
	{
		return;
	}

	m_vImGuiPase.push_back(ShaResView);
}

void CPase::SetRasState(ID3D11RasterizerState* RasState)
{
	m_DevCont->g_pImmediateContext->RSSetState(RasState);
}

void CPase::SetDepthSten(ID3D11DepthStencilState* DevStSt, UINT Val )
{
	m_DevCont->g_pImmediateContext->OMSetDepthStencilState(DevStSt, Val);
}

void CPase::ReleasePase()
{
	for (int i = 0; i < m_vTexts.size(); i++)
	{
		m_vTexts[i]->m_pTexture->Release();
		m_vRenTarView[i]->Release();
		m_vImGuiPase[i]->Release();
	}

	m_vTexts.clear();
	m_vRenTarView.clear();
	m_vImGuiPase.clear();

	ClearShaders();
}

void CPase::ClearShaders()
{
	for (int i = 0; i < m_vShadResView.size(); i++)
	{
		m_vShadResView[i] = nullptr;
	}
	m_vShadResView.clear();
}



