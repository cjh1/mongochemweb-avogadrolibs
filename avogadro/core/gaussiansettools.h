/******************************************************************************

  This source file is part of the Avogadro project.

  Copyright 2008-2009 Marcus D. Hanwell
  Copyright 2008 Albert De Fusco
  Copyright 2010-2013 Kitware, Inc.

  This source code is released under the New BSD License, (the "License").

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

******************************************************************************/

#ifndef AVOGADRO_CORE_GAUSSIANSETTOOLS_H
#define AVOGADRO_CORE_GAUSSIANSETTOOLS_H

#include "avogadrocore.h"

#include "vector.h"

#include <vector>

namespace Avogadro {
namespace Core {

class GaussianSet;
class Molecule;

/**
 * @class GaussianSetTools gaussiansettools.h <avogadro/core/gaussiansettools.h>
 * @brief Provide tools to calculate molecular orbitals, electron densities and
 * other derived data stored in a GaussianSet result.
 * @author Marcus D. Hanwell
 */

class AVOGADROCORE_EXPORT GaussianSetTools
{
public:
  explicit GaussianSetTools(Molecule *mol = 0);
  ~GaussianSetTools();

  /**
   * @brief Calculate the value of the specified molecular orbital at the
   * position specified.
   * @param position The position in space to calculate the value.
   * @param molecularOrbitalNumber The molecular orbital number.
   * @return The value of the molecular orbital at the position specified.
   */
  double calculateMolecularOrbital(const Vector3 &position,
                                   int molecularOrbitalNumber) const;

  /**
   * @brief Calculate the value of the electron density at the position
   * specified.
   * @param position The position in space to calculate the value.
   * @return The value of the electron density at the position specified.
   */
  double calculateElectronDensity(const Vector3 &position) const;

  /**
   * @brief Calculate the value of the electron spin density at the position
   * specified.
   * @param position The position in space to calculate the value.
   * @return The value of the spin density at the position specified.
   */
  double calculateSpinDensity(const Vector3 &position) const;

  /**
   * @brief Check that the basis set is valid and can be used.
   * @return True if valid, false otherwise.
   */
  bool isValid() const;

private:
  Molecule *m_molecule;
  GaussianSet *m_basis;

  bool isSmall(double value) const;

  /**
   * @brief Calculate the values at this position in space. The public calculate
   * functions call this function to prepare values before multiplying by the
   * molecular orbital or density matrix elements.
   * @param position The position in space to calculate the value.
   */
  std::vector<double> calculateValues(const Vector3 &position) const;

  void pointS(unsigned int index, double dr2,
              std::vector<double> &values) const;
  void pointP(unsigned int index, const Vector3 &delta, double dr2,
              std::vector<double> &values) const;
  void pointD(unsigned int index, const Vector3 &delta, double dr2,
              std::vector<double> &values) const;
  void pointD5(unsigned int index, const Vector3 &delta, double dr2,
               std::vector<double> &values) const;
};

} // End Core namespace
} // End Avogadro namespace

#endif // AVOGADRO_CORE_GAUSSIANSETTOOLS_H
