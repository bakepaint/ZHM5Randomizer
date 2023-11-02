#include "SSceneInitParameters.h"

#include "src/Console.h"

void SSceneInitParameters::print() const {
  hitman_randomizer::log::info("SSceneInitParameter hash: {}", std::hash<SSceneInitParameters>()(*this));
  hitman_randomizer::log::info("\t{}", m_SceneResource.to_string().c_str());
  for (int i = 0; i < m_aAdditionalBrickResources.size(); ++i)
    hitman_randomizer::log::info("\t\t{}", m_aAdditionalBrickResources[i].to_string().c_str());
}
