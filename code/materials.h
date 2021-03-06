/*************************************************************************/
/*                                                                       */
/*         Copyright (C) Antonio Gutierrez Martinez [2010]               */
/*                                                                       */
/*         License: GPL3                                                 */
/*                                                                       */
/*************************************************************************/
/**
 * @file materials.h
 * @brief Define the type of materials that could be used in the program
 * @author Antonio Gutierrez Martinez
 *
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef MATERIALS_H
#define MATERIALS_H

/**
 * @brief Estructura usada para definir un material.
 */
struct material
{
    _vertex4f _ambient;
    _vertex4f _diffuse;
    _vertex4f _specular;
    float _shininess;

    /**
     * @brief Constructor por defecto
     */
    material () {
        this->_ambient.r=0;this->_ambient.g=0;this->_ambient.b=0;this->_ambient.a=0;
        this->_diffuse.r=0;this->_diffuse.g=0;this->_diffuse.b=0;this->_diffuse.a=0;
        this->_specular.r=0;this->_specular.g=0;this->_specular.b=0;this->_specular.a=0;
        this->_shininess=0;
    }

    /**
     * @brief Constructor con parametros
     */
    material( float ambientR , float ambientG , float ambientB ,
              float diffuseR , float diffuseG , float diffuseB ,
              float specularR , float specularG , float specularB ,
              float shine ) {
        this->_ambient.r=ambientR;this->_ambient.g=ambientG;this->_ambient.b=ambientB;this->_ambient.a=1.0;
        this->_diffuse.r=diffuseR;this->_diffuse.g=diffuseG;this->_diffuse.b=diffuseB;this->_diffuse.a=1.0;
        this->_specular.r=specularR;this->_specular.g=specularG;this->_specular.b=specularB;this->_specular.a=1.00;
        this->_shininess=shine;
    }
};


///Materiales predefinidos
const material blackColor( 0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.25*128.0);
const material greenColor( 0.0,1,0.0,0.4,0.5,0.4,0.04,0.7,0.04,0.78125*128.0);
const material eggColor (0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.9,0.25*128.0);
const material rojizoColor (1,0.2,0.2,0.8,0.2,0.2,0.5,0.2,0.2,0.2*128.0);
const material orangeColor (0.2125,0.1275,0.054,0.714,0.4284,0.18144,0.393548,0.271906,0.166721,0.2);

const material emeraldColor (0.021,0.1745,0.0215,0.07568,0.61424,0.07568,0.633,0.727811,0.633,0.6*128.0 );
const material jadeColor (0.135,0.2225,0.1575,0.54	,0.89,0.63,0.316228,0.316228,0.316228,0.1*128.0);
const material obsidianColor (0.05375,0.05,0.06625,0.18275,0.17,0.22525,0.332741,0.328634,0.346435,0.3*128.0);
const material pearlColor (0.25,0.20725,0.20725,1,0.829,0.829,0.296648,0.296648,0.296648,0.088*128.0);
const material rubyColor (0.1745,0.01175,0.01175,0.61424,0.04136,0.04136,0.727811,0.626959,0.626959,0.6*128.0);
const material turquoiseColor (0.1,0.18725,0.1745,0.396,0.74151,0.69102,0.297254,0.30829,0.306678,0.1*128.0);
const material brassColor (0.329412,0.223529,0.027451,0.780392,0.568627,0.113725,0.992157,0.941176,0.807843,0.21794872*128.0);
const material bronzeColor (0.2125,0.1275,0.054,0.714,0.4284,0.18144,0.393548,0.271906,0.166721,0.2*128.0);
const material chromeColor (0.25,0.25,0.25,0.4,0.4,0.4,0.774597,0.774597,0.774597,0.6*128.0);
const material copperColor (0.19125,0.0735,0.0225,0.7038,0.27048,0.0828,0.256777,0.137622,0.086014,0.1);
const material goldColor (0.24725,0.1995,0.0745,0.75164,0.60648,0.22648,0.628281,0.555802,0.366065,0.4);
const material silverColor (0.19225,0.19225,0.19225,0.50754,0.50754,0.50754,0.508273,0.508273,0.508273,0.4*128.0);
const material blackPlasticColor (0.0,0.0,0.0,0.01,0.01,0.01,0.50,0.50,0.50,.25*128.0);
const material cyanPlasticColor (0.0,0.1,0.06,0.0,0.8,0.8,0.8,0.8,0.8,.25*128.0);
const material greenPlasticColor (0.0,0.0,0.0,0.1,0.35,0.1,0.45,0.55,0.45,.25*128.0);
const material redPlasticColor (0.0,0.0,0.0,0.5,0.0,0.0,0.7,0.6,0.6,.25*128.0);
const material whitePlasticColor (0.0,0.0,0.0,0.55,0.55,0.55,0.70,0.70,0.70,.25);
const material yellowPlasticColor (0.0,0.0,0.0,0.5,0.5,0.0,0.60,0.60,0.50,.25);
const material blackRubberColor (0.02,0.02,0.02,0.01,0.01,0.01,0.4,0.4,0.4,.078125*128.0);
const material cyanRubberColor (0.0,0.05,0.05,0.4,0.5,0.5,0.04,0.7,0.7,.078125*128.0);
const material greenRubberColor (0.0,0.05,0.0,0.4,0.5,0.4,0.04,0.7,0.04,.078125*128.0);
const material redRubberColor (0.05,0.0,0.0,0.5,0.4,0.4,0.7,0.04,0.04,.078125*128.0);
const material whiteRubberColor (0.05,0.05,0.05,0.5,0.5,0.5,0.7,0.7,0.7,.078125*128.0);
const material yellowRubberColor (0.05,0.05,0.0,0.5,0.5,0.4,0.7,0.7,0.04,.078125*128.0);

#endif // MATERIALS_H
