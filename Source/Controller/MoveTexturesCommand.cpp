/*
 Copyright (C) 2010-2012 Kristian Duske
 
 This file is part of TrenchBroom.
 
 TrenchBroom is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 TrenchBroom is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with TrenchBroom.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "MoveTexturesCommand.h"

#include "Model/EditStateManager.h"
#include "Model/Face.h"

#include <cassert>

namespace TrenchBroom {
    namespace Controller {
        bool MoveTexturesCommand::performDo() {
            Model::FaceList::const_iterator it, end;
            for (it = m_faces.begin(), end = m_faces.end(); it != end; ++it) {
                Model::Face& face = **it;
                face.moveTexture(m_up, m_right, m_direction, m_distance);
            }
            
            return true;
        }
        
        bool MoveTexturesCommand::performUndo() {
            Model::FaceList::const_iterator it, end;
            for (it = m_faces.begin(), end = m_faces.end(); it != end; ++it) {
                Model::Face& face = **it;
                face.moveTexture(m_up, m_right, m_direction, -m_distance);
            }
            
            return true;
        }
        
        MoveTexturesCommand::MoveTexturesCommand(Model::MapDocument& document, const wxString& name, const Model::FaceList& faces, const Vec3f& up, const Vec3f& right, Direction direction, float distance) :
        DocumentCommand(MoveTextures, document, true, name, true),
        m_faces(faces),
        m_up(up),
        m_right(right),
        m_direction(direction),
        m_distance(distance) {}

        MoveTexturesCommand* MoveTexturesCommand::moveTextures(Model::MapDocument& document, const Model::FaceList& faces, const Vec3f& up, const Vec3f& right, Direction direction, float distance) {
            const wxString name = faces.size() == 1 ? wxT("Move Texture") : wxT("Move Textures");
            return new MoveTexturesCommand(document, name, faces, up, right, direction, distance);
        }
    }
}
