#include "objects.h"
#include <iostream>

/*************************************************/
//CLASS _OBJECT3D
/*************************************************/

_object3D::_object3D(){
    _compiled = false;
    this->_colorRGB.r=0;this->_colorRGB.g=0;this->_colorRGB.b=0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

_object3D::~_object3D(){
    this->_vertices.clear();
    this->_faces.clear();
    this->_normal_faces.clear();
    this->_normal_vertices.clear();
    if (!this->_image.isNull()) {
        glDeleteTextures(1,&_texture);
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void _object3D::setColor(const _vertex3f &c){
    this->_colorRGB=c;
}
_vertex3f _object3D::getColor(){
    return this->_colorRGB;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void _object3D::setVertices(const vector<_vertex3f> &v ){
    this->_vertices.clear();
    this->_vertices=v;
}
vector<_vertex3f> _object3D::getVertices(){
    return this->_vertices;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void _object3D::setFaces(const vector<face> &v ){
    this->_faces.clear();
    this->_faces=v;
}
vector<face> _object3D::getFaces(){
    return this->_faces;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void _object3D::setMaterial(const material &m) {
    _colors._ambient = m._ambient;
    _colors._shininess = m._shininess;
    _colors._diffuse = m._diffuse;
    _colors._specular = m._specular;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void _object3D::compile() {

    _list[0] = glGenLists(1);
    glNewList(_list[0], GL_COMPILE);
    this->drawPoints();
    glEndList();

    _list[1] = glGenLists(1);
    glNewList(_list[1], GL_COMPILE);
    this->drawLines();
    glEndList();

    _list[2] = glGenLists(1);
    glNewList(_list[2], GL_COMPILE);
    this->drawRGB();
    glEndList();

    _list[3] = glGenLists(1);
    glNewList(_list[3], GL_COMPILE);
    this->drawChess();
    glEndList();

    _list[4] = glGenLists(1);
    glNewList(_list[4], GL_COMPILE);
    this->drawPlane();
    glEndList();

    _list[5] = glGenLists(1);
    glNewList(_list[5], GL_COMPILE);
    this->drawGouraud();
    glEndList();

    _list[6] = glGenLists(1);
    glNewList(_list[6], GL_COMPILE);
    this->drawTexture();
    glEndList();

    _compiled = true;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void _object3D::drawPoints() {
    glColor3f(this->_colorRGB.r,this->_colorRGB.g,this->_colorRGB.b);

    glBegin(GL_POINTS);
    for (int i=0 ; i<_vertices.size(); i++) {
        glVertex3f(_vertices[i].x,_vertices[i].y,_vertices[i].z);
    }
    glEnd();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void _object3D::drawLines() {
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINES);
    glColor3f(this->_colorRGB.r,this->_colorRGB.g,this->_colorRGB.b);
    glBegin(GL_TRIANGLES);
    int kv1 , kv2, kv3;
    for (int i=0 ; i<_faces.size(); i++){
        kv1=_faces[i].v1;kv2=_faces[i].v2;kv3=_faces[i].v3;
        glVertex3f(_vertices[kv1].x,_vertices[kv1].y,_vertices[kv1].z);
        glVertex3f(_vertices[kv2].x,_vertices[kv2].y,_vertices[kv2].z);
        glVertex3f(_vertices[kv3].x,_vertices[kv3].y,_vertices[kv3].z);
    }
    glEnd();

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void _object3D::drawRGB(){
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glColor3f(this->_colorRGB.r,this->_colorRGB.g,this->_colorRGB.b);

    glBegin(GL_TRIANGLES);
    int kv1 , kv2, kv3;
    for (int i=0 ; i<_faces.size(); i++){
        kv1=_faces[i].v1;kv2=_faces[i].v2;kv3=_faces[i].v3;
        glVertex3f(_vertices[kv1].x,_vertices[kv1].y,_vertices[kv1].z);
        glVertex3f(_vertices[kv2].x,_vertices[kv2].y,_vertices[kv2].z);
        glVertex3f(_vertices[kv3].x,_vertices[kv3].y,_vertices[kv3].z);
    }
    glEnd();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void _object3D::drawChess(){
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    glBegin(GL_TRIANGLES);
    int kv1 , kv2, kv3;
    for (int i=0 ; i<_faces.size(); i++){
        kv1=_faces[i].v1;kv2=_faces[i].v2;kv3=_faces[i].v3;
        (i%2==0)?glColor3f(1,0,0):glColor3f(0,1,0);
         glVertex3f(_vertices[kv1].x,_vertices[kv1].y,_vertices[kv1].z);
         glVertex3f(_vertices[kv2].x,_vertices[kv2].y,_vertices[kv2].z);
         glVertex3f(_vertices[kv3].x,_vertices[kv3].y,_vertices[kv3].z);
    }
    glEnd();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void _object3D::drawPlane(){

    // Dibujado de las caras del objeto 3D
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    //activamos la luz
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    //definimos el material
    glMaterialfv(GL_FRONT,GL_AMBIENT,(const GLfloat *)&_colors._ambient);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,(const GLfloat *)&_colors._diffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR,(const GLfloat *)&_colors._specular);
    glMaterialf(GL_FRONT,GL_SHININESS,_colors._shininess);

    //tipo suaviazado
    glShadeModel(GL_FLAT);

    glBegin(GL_TRIANGLES);
    int kv1 , kv2, kv3;
    for (int i=0 ; i<_faces.size(); i++){
        kv1=_faces[i].v1;kv2=_faces[i].v2;kv3=_faces[i].v3;
        glNormal3f(this->_normal_faces[i].x,this->_normal_faces[i].y,this->_normal_faces[i].z);
        glVertex3f(_vertices[kv1].x,_vertices[kv1].y,_vertices[kv1].z);
        glVertex3f(_vertices[kv2].x,_vertices[kv2].y,_vertices[kv2].z);
        glVertex3f(_vertices[kv3].x,_vertices[kv3].y,_vertices[kv3].z);
    }
    glEnd();

    //quitamos la luz
    glDisable(GL_LIGHTING);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void _object3D::drawGouraud(){
    // Dibujado de las caras del objeto 3D
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINES);

    //activamos la luz
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    //definimos el material
    glMaterialfv(GL_FRONT,GL_AMBIENT,(const GLfloat *)&_colors._ambient);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,(const GLfloat *)&_colors._diffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR,(const GLfloat *)&_colors._specular);
    glMaterialf(GL_FRONT,GL_SHININESS,_colors._shininess);

    //tipo suaviazado
    glShadeModel(GL_SMOOTH);

    glBegin(GL_TRIANGLES);
    int kv1 , kv2, kv3;
    for (int i=0 ; i<_faces.size(); i++){
        kv1=_faces[i].v1;kv2=_faces[i].v2;kv3=_faces[i].v3;
        glNormal3f(this->_normal_vertices[kv1].x,this->_normal_vertices[kv1].y,this->_normal_vertices[kv1].z);
        glVertex3f(_vertices[kv1].x,_vertices[kv1].y,_vertices[kv1].z);
        glNormal3f(this->_normal_vertices[kv2].x,this->_normal_vertices[kv2].y,this->_normal_vertices[kv2].z);
        glVertex3f(_vertices[kv2].x,_vertices[kv2].y,_vertices[kv2].z);
        glNormal3f(this->_normal_vertices[kv3].x,this->_normal_vertices[kv3].y,this->_normal_vertices[kv3].z);
        glVertex3f(_vertices[kv3].x,_vertices[kv3].y,_vertices[kv3].z);
    }
    glEnd();

    //quitamos la luz
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void _object3D::drawTexture() {
    glColor3f(1.0,1.0,1.0);
    glEnable(GL_TEXTURE_2D);

    glBindTexture( GL_TEXTURE_2D, _texture );
    glTexImage2D( GL_TEXTURE_2D, 0, 3, _image.width(), _image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, _image.bits() );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glBegin(GL_QUADS);
    int kv1 , kv2, kv3;
    for (int i=0 ; i<_faces.size(); i++){
        kv1=_faces[i].v1;kv2=_faces[i].v2;kv3=_faces[i].v3;
        glTexCoord2f(0.0f,0.0f);glVertex3f(_vertices[kv1].x,_vertices[kv1].y,_vertices[kv1].z);
        glTexCoord2f(0.0f,1.0f);glVertex3f(_vertices[kv2].x,_vertices[kv2].y,_vertices[kv2].z);
        glTexCoord2f(1.0f,1.0f);glVertex3f(_vertices[kv3].x,_vertices[kv3].y,_vertices[kv3].z);
        glTexCoord2f(1.0f,0.0f);glVertex3f(_vertices[kv1].x,_vertices[kv1].y,_vertices[kv1].z);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void _object3D::setTexture(const char *file) {
    if (!_image.load( file   ) ) {
        printf ("Error al cargar la imagen: %s",file);
        exit(-1);
    }

    _image = QGLWidget::convertToGLFormat( _image );
    glGenTextures( 1, &_texture );
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void _object3D::draw( drawMode d ) {
    if (!_compiled) this->compile();

    switch (d) {
    case points:
        glCallList(_list[0]);
        break;
    case lines:
        glCallList(_list[1]);
        //drawLines();
        break;
    case rgb:
        glCallList(_list[2]);
        break;
    case chess:
        glCallList(_list[3]);
        break;
    case plane:
        glCallList(_list[4]);
        break;
    case gouraud:
        glCallList(_list[5]);
        break;
    case texture:
        glCallList(_list[6]);
        break;
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void _object3D::createNormals(){
    _vertex3f aux1, aux2,aux3 ;

    //Preparamos el vector de normales de los vertices
    for (int i=0 ; i<this->_vertices.size() ; i++){
        _vertex3f aux;
        this->_normal_vertices.push_back(aux);
    }

    //Calculamos para cada cara su normal
    for (int i=0 ; i<this->_faces.size(); i++) {
        aux1=this->_vertices[_faces[i].v2]-this->_vertices[_faces[i].v1];
        aux2=this->_vertices[_faces[i].v3]-this->_vertices[_faces[i].v1];
        aux3=aux1.cross_product(aux2);
        aux3=aux3.normalize();
        //añadimos la normal de la cara
        this->_normal_faces.push_back(aux3);

        //actualizamos las normales de vertices
        this->_normal_vertices[_faces[i].v1]+=aux3;
        this->_normal_vertices[_faces[i].v2]+=aux3;
        this->_normal_vertices[_faces[i].v3]+=aux3;
    }

    //calculamos los valores de la normal a los vertices
    for (int i=0 ; i<this->_normal_vertices.size() ; i++){
        this->_normal_vertices[i]=this->_normal_vertices[i].normalize();
    }

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void _object3D::calculateBox() {
    this->_Xmin=_vertices[0].x; this->_Ymin=_vertices[0].y; this->_Zmin=_vertices[0].z;
    this->_Xmax=_vertices[0].x; this->_Ymax=_vertices[0].y; this->_Zmax=_vertices[0].z;

    //Calculamos los extremos de la caja
    for ( int i=1 ; i<_vertices.size() ; i++ ) {
        if (_vertices[i].x<_Xmin) _Xmin=_vertices[i].x;
        if (_vertices[i].y<_Ymin) _Ymin=_vertices[i].y;
        if (_vertices[i].z<_Zmin) _Zmin=_vertices[i].z;
        if (_vertices[i].x>_Xmax) _Xmax=_vertices[i].x;
        if (_vertices[i].y>_Ymax) _Ymax=_vertices[i].y;
        if (_vertices[i].z>_Zmax) _Zmax=_vertices[i].z;
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

float _object3D::collisionRadius() {
    float xmedio,ymedio,zmedio;

    xmedio=(_Xmin+_Xmax)/2;
    ymedio=(_Ymin+_Ymax)/2;
    zmedio=(_Zmin+_Zmax)/2;

    _vertex3f aux;
    aux.x=_Xmax-xmedio;
    aux.y=_Ymax-ymedio;
    aux.z=_Zmax-zmedio;

    return aux.module();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

float _object3D::Ymax() { return this->_Ymax;}
float _object3D::Ymin() { return this->_Ymin;}
float _object3D::Xmax() { return this->_Xmax;}
float _object3D::Xmin() { return this->_Xmin;}
float _object3D::Zmax() { return this->_Zmax;}
float _object3D::Zmin() { return this->_Zmin;}

/*************************************************/
//CLASS OBJECT3DPLY
/*************************************************/

Object3DPly::Object3DPly( char *fichero ){
    this->_path = fichero;
    this->createObject();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Object3DPly::createObject( ){
    vector<float> v;
    vector<int> c;

    //leemos el fichero .ply
    _file_ply f;
    f.open(_path);
    f.read(v,c);
    f.close();
    _vertex3f aux;
    //Creamos el vector de vertices
    for (int i=0 ; i<v.size();i+=3 ){
           aux.x=v[i];
           aux.y=v[i+1];
           aux.z=v[i+2];
           this->_vertices.push_back(aux);
    }

    face aux2;
    //Creamos las caras
    for (int i=0 ; i<c.size();i+=3 ) {
        aux2.v1=c[i];
        aux2.v2=c[i+1];
        aux2.v3=c[i+2];
        this->_faces.push_back(aux2);
    }

    //Creamos las normales
    this->createNormals();

    //Calculamos los extremos
    this->calculateBox();
}

/*************************************************/
//CLASS CONE
/*************************************************/

Cone::Cone(float radius , float hight , int faces){
    this->_radius=radius;
    this->_high=hight;
    this->_numFaces=faces;
    this->createObject();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

float Cone::getHight() { return this->_high;}
int Cone::getNumFaces() { return this->_numFaces; }
float Cone::getRadius() { return this->_radius; }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Cone::createObject(){
    this->_vertices.clear();
    this->_faces.clear();
    _vertex3f v1;
    face f;

    //CREAMOS LOS PUNTOS
    //Creamos el circulo inferior
    for ( int i=0 ; i<this->_numFaces ; i++) {
        v1.x=this->_radius*cos( (2*PI*i)/this->_numFaces);
        v1.y=-this->_high/2;
        v1.z=this->_radius*sin( (2*PI*i)/this->_numFaces);
        this->_vertices.push_back(v1);
    }
    //Ponemos el centro inferior
    v1.x=0;
    v1.y=-this->_high/2;
    v1.z=0;
    this->_vertices.push_back(v1);
    //Ponemos el pico
    v1.x=0;
    v1.y=this->_high/2;
    v1.z=0;
    this->_vertices.push_back(v1);

    //CREAMOS LAS CARAS
    //laterales (sentido antihorario)
    f.v1=_vertices.size()-1;
    for (int i=0 ; i<_numFaces ; i++ ){
        f.v2=i+1;
        if (i!=_numFaces-1)
            f.v3=i;
        else {
            f.v2 = 0 ;
            f.v3=_numFaces-1;
        }
        _faces.push_back(f);
    }

    //tapa inferior
    f.v1=_vertices.size()-2;
    for (int i=0 ; i<_numFaces ; i++ ) {
            f.v2=i;
            if (i!=_numFaces-1)
                f.v3=i+1;
            else
                f.v3=0;
            _faces.push_back(f);
    }

    //CREAMOS LAS NORMALES
    this->createNormals();

    //Calculamos los extremos
    this->calculateBox();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Cone::Parameters(float radio , float altura , int caras){
        this->_radius=radio;
        this->_high=altura;
        this->_numFaces=caras;
        this->createObject();
}

/*************************************************/
//CLASS Cube
/*************************************************/
Cube::Cube(float lado){
    this->_side=lado;
    this->createObject();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Cube::createObject(){
    this->_vertices.clear();
    this->_faces.clear();
    face f;
    _vertex3f aux;

    //Insertamos los puntos de la tapa inferior
    //Punto1
    aux.x=-this->_side/2; aux.y=-this->_side/2; aux.z=this->_side/2;
    this->_vertices.push_back(aux);
    //Punto2
    aux.x=this->_side/2; aux.y=-this->_side/2; aux.z=this->_side/2;
    this->_vertices.push_back(aux);
    //Punto3
    aux.x=this->_side/2; aux.y=-this->_side/2; aux.z=-this->_side/2;
    this->_vertices.push_back(aux);
    //Punto4
    aux.x=-this->_side/2; aux.y=-this->_side/2; aux.z=-this->_side/2;
    this->_vertices.push_back(aux);
    //Insertamos los puntos de la tapa superior
    //Punto5
    aux.x=-this->_side/2; aux.y=this->_side/2; aux.z=this->_side/2;
    this->_vertices.push_back(aux);
    //Punto6
    aux.x=this->_side/2; aux.y=this->_side/2; aux.z=this->_side/2;
    this->_vertices.push_back(aux);
    //Punto7
    aux.x=this->_side/2; aux.y=this->_side/2; aux.z=-this->_side/2;
    this->_vertices.push_back(aux);
    //Punto8
    aux.x=-this->_side/2; aux.y=this->_side/2; aux.z=-this->_side/2;
    this->_vertices.push_back(aux);

    //CARAS
    //laterales
    for ( int i=0 ; i<4 ; i++ ) {
        f.v1=i;
        if (i!=0 ) {
            f.v2=i+4;
            f.v3=i-1;
            _faces.push_back(f);
            f.v1=i-1; f.v2=i+4; f.v3=i+3;
        }else {
            f.v2=4; f.v3=3;
            _faces.push_back(f);
            f.v1=3; f.v2=4;f.v3=7;
        }
        _faces.push_back(f);
    }

    //inferior
    f.v1=1; f.v2=0; f.v3=3;
    _faces.push_back(f);
    f.v1=1; f.v2=3; f.v3=2;
    _faces.push_back(f);

    //superior
    f.v1=4; f.v2=5; f.v3=7;
    _faces.push_back(f);
    f.v1=f.v2; f.v2=6; f.v3=7;
    _faces.push_back(f);

    //Creamos las normales
    this->createNormals();

    //Calculamos los extremos
    this->calculateBox();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Cube::Parameters(float lado){
    this->_side=lado;
    this->createObject();
}

float Cube::getSide() {
    return this->_side;
}

/*************************************************/
//CLASS CILINDRO
/*************************************************/

Cylinder::Cylinder(float radio, float altura , int caras){
    this->_radius=radio;
    this->_high=altura;
    this->_numFaces=caras;
    this->createObject();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Cylinder::createObject(){
    this->_vertices.clear();
    this->_faces.clear();

    face f;
    _vertex3f v1;

    //PUNTOS
    //Creamos el circulo inferior
    for ( int i=0 ; i<this->_numFaces ; i++) {
        v1.x=this->_radius*cos( (2*PI*i)/this->_numFaces);
        v1.y=-this->_high/2;
        v1.z=this->_radius*sin( (2*PI*i)/this->_numFaces);
        this->_vertices.push_back(v1);
    }
    //Creamos el circulo superior
    for ( int i=0 ; i<this->_numFaces ; i++) {
        v1.x=this->_radius*cos( (2*PI*i)/this->_numFaces);
        v1.y=this->_high/2;
        v1.z=this->_radius*sin( (2*PI*i)/this->_numFaces);
        this->_vertices.push_back(v1);
    }
    //Ponemos el centro inferior
    v1.x=0;
    v1.y=-this->_high/2;
    v1.z=0;
    this->_vertices.push_back(v1);
    //Ponemos el centro superior
    v1.x=0;
    v1.y=this->_high/2;
    v1.z=0;
    this->_vertices.push_back(v1);

    //CARAS
    //tapa inferior
    f.v1=_vertices.size()-2;
    for (int i=0 ; i<_numFaces ; i++ ) {
        f.v2=i;
        if (i!=_numFaces-1)
            f.v3=i+1;
        else
            f.v3=0;
        _faces.push_back(f);
    }
    //tapa superior
    f.v1=_vertices.size()-1;
    for (int i=_numFaces ; i<(_numFaces*2) ; i++ ) {
        f.v2=i+1;
        if (i!=(_numFaces*2)-1)
            f.v3=i;
        else {
            f.v3=i;
            f.v2 = _numFaces;
        }
        _faces.push_back(f);
    }
    //caras laterales
    for (int i=0 ; i<_numFaces ; i++ ) {
        f.v1=i+1;
        if (i!=(_numFaces-1)){
            f.v2=i;
            f.v3=i+_numFaces;
            _faces.push_back(f);
            f.v2=f.v3;
            f.v3=i+_numFaces+1;
        }else {
            f.v1 = 0;
            f.v2= _numFaces-1;
            f.v3=i+_numFaces;
            _faces.push_back(f);
            f.v2=f.v3;
            f.v3=_numFaces;
        }
        _faces.push_back(f);
    }

    //Creamos las normales
    this->createNormals();

    //Calculamos los extremos
    this->calculateBox();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Cylinder::Parameters(float radio, float altura , int caras){
    this->_radius=radio;
    this->_high=altura;
    this->_numFaces=caras;
    this->createObject();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

float Cylinder::getHigh() { return _high;}
float Cylinder::getRadius() { return _radius; }

/*************************************************/
//CLASS Sphere
/*************************************************/

Sphere::Sphere(float radio, int caras) {
    this->_radius=radio;
    this->_numFaces=caras;
    this->createObject();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Sphere::createObject() {

    this->_vertices.clear();
    this->_faces.clear();

    //variables auxiliares
    vector<_vertex3f> aux;
    _vertex3f v1;
    float r , h;
    face f;
    int inicio;

    //Creamos media esfera vertical
    for ( int i=0 ; i<this->_numFaces/2+1 ; i++) {
        v1.x=this->_radius*sin( (2*PI*i)/this->_numFaces);
        v1.y=this->_radius*cos( (2*PI*i)/this->_numFaces);
        v1.z=0;
        aux.push_back(v1);
    }

    //Para cada uno de esos puntos hacemos un circulo horizontal y guardamos los puntos
    this->_vertices.push_back(aux[0]);
    for (int i=1 ; i<aux.size()-1;i++) {
        h=aux[i].y;
        r=aux[i].x;
        for ( int j=0 ; j<this->_numFaces ; j++ ){
            v1.x=r*cos( (2*PI*j)/this->_numFaces);
            v1.y=h;
            v1.z=r*sin( (2*PI*j)/this->_numFaces);
            this->_vertices.push_back(v1);
        }
    }
    this->_vertices.push_back(aux[aux.size()-1]);

    //FORMAMOS LAS CARAS
    //pico superior
    f.v1=0;
    for (int i=1 ; i<_numFaces+1 ; i++ ) {
        f.v2=i+1;
        if (i!=_numFaces)
            f.v3=i;
        else {
            f.v2=1;
            f.v3=_numFaces;
        }
        _faces.push_back(f);
    }
    //pico inferior
    f.v1=_vertices.size()-1;
    inicio=(aux.size()-3)*this->_numFaces+1;
    for (int i=inicio ; i<(aux.size()-2)*this->_numFaces+1 ; i++ ) {
        f.v2=i;
        if (i!=(aux.size()-2)*this->_numFaces)
            f.v3=i+1;
        else
            f.v3=inicio;
        _faces.push_back(f);
    }

    //creamos las caras centrales
    for ( int i=0 ; i<aux.size()-3 ; i++ ) {

        for (int j=_numFaces*i+1 ; j<(_numFaces*i+_numFaces)+1 ; j++ ) {
            f.v1=j;
            if (j!=(_numFaces*i+_numFaces)){
                f.v2=j+1;
                f.v3=j+_numFaces;
                _faces.push_back(f);
                f.v1=f.v2;
                f.v2=j+_numFaces+1;
                f.v3=f.v3;
            }else {
                f.v2=_numFaces*i+1;
                f.v3=j+_numFaces;
                _faces.push_back(f);
                f.v1=f.v2;
                f.v3=f.v3;
                f.v2=_numFaces*i+1+_numFaces;
            }
            _faces.push_back(f);
        }
    }

    //creamos las normales
    createNormals();

    //Calculamos los extremos
    this->calculateBox();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Sphere::Parameters(float radio , int caras) {
    this->_radius=radio;
    this->_numFaces=caras;
    this->createObject();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

float Sphere::getRadius() { return this->_radius; }

/*************************************************/
//CLASS SemiEsfera
/*************************************************/

SemiSphere::SemiSphere(float radio, int caras) {
    this->_radius=radio;
    this->_numFaces=caras;
    this->createObject();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void SemiSphere::createObject() {
    this->_vertices.clear();
    this->_faces.clear();

    //variables auxiliares
    vector<_vertex3f> aux;
    _vertex3f v1;
    float r , h;
    face f;

    //Creamos media semiSphere vertical
    for ( int i=0 ; i<this->_numFaces/4+2 ; i++) {
        v1.x=this->_radius*sin( (2*PI*i)/this->_numFaces);
        v1.y=this->_radius*cos( (2*PI*i)/this->_numFaces);
        v1.z=0;
        aux.push_back(v1);
        if ( i == this->_numFaces/4+1) {
            v1.x = v1.z = 0;
            aux.push_back(v1);
        }
    }

    //Para cada uno de esos puntos hacemos un circulo horizontal y guardamos los puntos
    this->_vertices.push_back(aux[0]);
    for (int i=1 ; i<aux.size()-1;i++) {
        h=aux[i].y;
        r=aux[i].x;
        for ( int j=0 ; j<this->_numFaces ; j++ ){
            v1.x=r*cos( (2*PI*j)/this->_numFaces);
            v1.y=h;
            v1.z=r*sin( (2*PI*j)/this->_numFaces);
            this->_vertices.push_back(v1);
        }
    }
    this->_vertices.push_back(aux[aux.size()-1]);

    //FORMAMOS LAS CARAS
    //pico superior
    f.v1=0;
    for (int i=1 ; i<_numFaces+1 ; i++ ) {
        f.v2=i+1;
        if (i!=_numFaces)
            f.v3=i;
        else{
            f.v2=1;
            f.v3=_numFaces;
        }
        _faces.push_back(f);
    }

    //creamos las caras centrales
    for ( int i=0 ; i<aux.size()-3 ; i++ ) {

        for (int j=_numFaces*i+1 ; j<(_numFaces*i+_numFaces)+1 ; j++ ) {
            f.v1=j;
            if (j!=(_numFaces*i+_numFaces)){
                f.v2=j+1;
                f.v3=j+_numFaces;
                _faces.push_back(f);
                f.v1=f.v2;
                f.v2=j+_numFaces+1;
                f.v3=f.v3;
            }else {
                f.v2=_numFaces*i+1;
                f.v3=j+_numFaces;
                _faces.push_back(f);
                f.v1=f.v2;
                f.v3=f.v3;
                f.v2=_numFaces*i+1+_numFaces;
            }
            _faces.push_back(f);
        }
    }

    //tampamos por debajo
    f.v1=_vertices.size()-1;
    int inicio=(aux.size()-3)*this->_numFaces+1;
    for (int i=inicio ; i<(aux.size()-2)*this->_numFaces+1 ; i++ ) {
        f.v2=i;
        if (i!=(aux.size()-2)*this->_numFaces)
            f.v3=i+1;
        else
            f.v3=inicio;
        _faces.push_back(f);
    }

    //creamos las normales
    createNormals();

    //Calculamos los extremos
    this->calculateBox();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void SemiSphere::Parameters(float radio , int caras) {
    this->_radius=radio;
    this->_numFaces=caras;
    this->createObject();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

float SemiSphere::getRadius() { return this->_radius; }

/*************************************************/
//CLASS Piramide
/*************************************************/

Pyramid::Pyramid(float hight, float side) {
    this->_high = hight;
    this->_side = side;
    this->createObject();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Pyramid::createObject() {
    this->_vertices.clear();
    this->_faces.clear();
    face f;
    _vertex3f aux;

    //VERTICES
    //Insertamos el pico superior
    aux.x = 0 ; aux.y = this->_side/2; aux.z = 0;
    this->_vertices.push_back(aux);
    //Insertamos los puntos de la tapa inferior
    //Punto1
    aux.x=-this->_side/2; aux.y=-this->_side/2; aux.z=this->_side/2;
    this->_vertices.push_back(aux);
    //Punto2
    aux.x=this->_side/2; aux.y=-this->_side/2; aux.z=this->_side/2;
    this->_vertices.push_back(aux);
    //Punto3
    aux.x=this->_side/2; aux.y=-this->_side/2; aux.z=-this->_side/2;
    this->_vertices.push_back(aux);
    //Punto4
    aux.x=-this->_side/2; aux.y=-this->_side/2; aux.z=-this->_side/2;
    this->_vertices.push_back(aux);

    //CARAS
    //inferior
    f.v1=2; f.v2=1; f.v3=4;
    _faces.push_back(f);
    f.v1=2; f.v2=4; f.v3=3;
    _faces.push_back(f);

    //laterales
    for ( int i=1 ; i<_vertices.size() ; i++ ) {
        f.v1 = i;
        if ( i!= _vertices.size()-1 ){
            f.v2 = i+1;
        }else
            f.v2 = 1;
        f.v3 = 0;
        _faces.push_back(f);
    }

    //creamos las normales
    createNormals();

    //Calculamos los extremos
    this->calculateBox();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Pyramid::Parameters(float hight, float side ) {
    this->_high = hight;
    this->_side = side;
    this->createObject();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

float Pyramid::getHigh() { return this->_high; }
float Pyramid::getSide() { return this->_side; }
