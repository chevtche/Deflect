/*********************************************************************/
/* Copyright (c) 2013, EPFL/Blue Brain Project                       */
/*                     Raphael Dumusc <raphael.dumusc@epfl.ch>       */
/* All rights reserved.                                              */
/*                                                                   */
/* Redistribution and use in source and binary forms, with or        */
/* without modification, are permitted provided that the following   */
/* conditions are met:                                               */
/*                                                                   */
/*   1. Redistributions of source code must retain the above         */
/*      copyright notice, this list of conditions and the following  */
/*      disclaimer.                                                  */
/*                                                                   */
/*   2. Redistributions in binary form must reproduce the above      */
/*      copyright notice, this list of conditions and the following  */
/*      disclaimer in the documentation and/or other materials       */
/*      provided with the distribution.                              */
/*                                                                   */
/*    THIS  SOFTWARE  IS  PROVIDED  BY  THE  ECOLE  POLYTECHNIQUE    */
/*    FEDERALE DE LAUSANNE  ''AS IS''  AND ANY EXPRESS OR IMPLIED    */
/*    WARRANTIES, INCLUDING, BUT  NOT  LIMITED  TO,  THE  IMPLIED    */
/*    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR  A PARTICULAR    */
/*    PURPOSE  ARE  DISCLAIMED.  IN  NO  EVENT  SHALL  THE  ECOLE    */
/*    POLYTECHNIQUE  FEDERALE  DE  LAUSANNE  OR  CONTRIBUTORS  BE    */
/*    LIABLE  FOR  ANY  DIRECT,  INDIRECT,  INCIDENTAL,  SPECIAL,    */
/*    EXEMPLARY,  OR  CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT NOT    */
/*    LIMITED TO,  PROCUREMENT  OF  SUBSTITUTE GOODS OR SERVICES;    */
/*    LOSS OF USE, DATA, OR  PROFITS;  OR  BUSINESS INTERRUPTION)    */
/*    HOWEVER CAUSED AND  ON ANY THEORY OF LIABILITY,  WHETHER IN    */
/*    CONTRACT, STRICT LIABILITY,  OR TORT  (INCLUDING NEGLIGENCE    */
/*    OR OTHERWISE) ARISING  IN ANY WAY  OUT OF  THE USE OF  THIS    */
/*    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.   */
/*                                                                   */
/* The views and conclusions contained in the software and           */
/* documentation are those of the authors and should not be          */
/* interpreted as representing official policies, either expressed   */
/* or implied, of Ecole polytechnique federale de Lausanne.          */
/*********************************************************************/

#include "Event.h"

#include <QDataStream>

namespace deflect
{
const uint32_t Event::serializedSize = 3 * sizeof(quint32) +
                                       4 * sizeof(double) + 3 * sizeof(bool) +
                                       UNICODE_TEXT_SIZE;

QDataStream& operator<<(QDataStream& out, const deflect::Event& event)
{
    out << (qint32)event.type;

    out << event.mouseX << event.mouseY;
    out << event.dx << event.dy;

    out << event.mouseLeft << event.mouseRight << event.mouseMiddle;

    out << (qint32)event.key << (qint32)event.modifiers;

    for (size_t i = 0; i < UNICODE_TEXT_SIZE; ++i)
        out << (quint8)event.text[i];

    return out;
}

QDataStream& operator>>(QDataStream& in, deflect::Event& event)
{
    qint32 type;
    in >> type;
    event.type = (Event::EventType)type;

    in >> event.mouseX >> event.mouseY;
    in >> event.dx >> event.dy;

    in >> event.mouseLeft >> event.mouseRight >> event.mouseMiddle;

    qint32 key, modifiers;
    in >> key >> modifiers;
    event.key = (int)key;
    event.modifiers = (int)modifiers;

    quint8 character;
    for (size_t i = 0; i < UNICODE_TEXT_SIZE; ++i)
    {
        in >> character;
        event.text[i] = (char)character;
    }

    return in;
}
}
