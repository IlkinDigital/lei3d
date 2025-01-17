#include "GuiRect.hpp"

#include "rendering/gui/GuiManager.hpp"
#include "rendering/gui/UiMesh.hpp"

namespace lei3d 
{
	GuiRect::GuiRect(
		Anchor anchor, 
		const std::pair<Space, glm::vec2>& pos, 
		const std::pair<Space, glm::vec2>& size, 
		glm::vec4 color
	)
		: GuiComponent(anchor, pos, size)
		, m_color(color)
	{
		std::vector<UiMesh::Vertex> vertices;
		std::vector<unsigned int> indices;

		vertices.emplace_back(UiMesh::Vec2{ 0.0f, 0.0f });
		vertices.emplace_back(UiMesh::Vec2{ 0.0f, 1.0f });
		vertices.emplace_back(UiMesh::Vec2{ 1.0f, 1.0f });
		vertices.emplace_back(UiMesh::Vec2{ 1.0f, 0.0f });

		indices.emplace_back(0);
		indices.emplace_back(1);
		indices.emplace_back(2);
		indices.emplace_back(0);
		indices.emplace_back(2);
		indices.emplace_back(3);

		m_mesh = new UiMesh(vertices, indices);
	}

	GuiRect::~GuiRect()
	{
		delete m_mesh;
	}

	void GuiRect::SetColor(const glm::vec4& color)
	{
		m_color = color;
	}

	void GuiRect::Render(const glm::vec2& screenSize)
	{
		GuiManager::Instance().m_guiShader.bind();

		GuiManager::Instance().m_guiShader.setUniformMat4("transform",
			glm::translate(glm::identity<glm::mat4>(), PosNormalized(screenSize)) *
			glm::scale(glm::identity<glm::mat4>(), glm::vec3(SizeNormalized(screenSize), 1)) 
		);

		GuiManager::Instance().m_guiShader.setVec2("screenSize", screenSize);
		GuiManager::Instance().m_guiShader.setVec4("color", m_color);
		GuiManager::Instance().m_guiShader.setInt("normalized", true);

		m_mesh->Draw(&GuiManager::Instance().m_guiShader);
	}

	void GuiRect::Update()
	{

	}
}
