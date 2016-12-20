"use strict";

var canvas;
var gl;
var selection=1;//
var vertexNum=216;//一共有多少个节点
var left_eye1;
var right_eye1;
var left_eye2;
var right_eye2;
var left_eye1_ball;
var right_eye1_ball;
var left_eye2_ball;
var right_eye2_ball;

var axis = 0;
var xAxis = 0;
var yAxis =1;
var zAxis = 2;
var theta = [ 0, 0, 0 ];
var thetaLoc;
//new
//动画类型
var anivation = [0, 0, 0];
var anivationLoc;

//动画比例
var scale = [0, 0, 0];
var scaleLoc;

var id = 0;
//end

//定义相机变换相关变量

var near = -1;
var far = 1;
var radius = 1.0;
var theta  = 0.0;
var phi    = 0.0;
var dr = 5.0 * Math.PI/180.0;
var left = -1.0;
var right = 1.0;
var ytop = 1.0;
var bottom = -1.0;
var  fovy = 45.0;  // Field-of-view in Y direction angle (in degrees)
var  aspect;       // Viewport aspect ratio
var modelViewMatrix, projectionMatrix;
var modelView, projection;

var sunx=1.0;
var suny=1.0;
var sunz=1.0;
var flag = true;
var modelViewMatrixLoc, projectionMatrixLoc;
var normalMatrix, normalMatrixLoc;

var eye;
const at = vec3(0.0, 0.0, 0.0);
const up = vec3(0.0, 1.0, 0.0);

var pointsArray = [];
var normalsArray = [];
//光源属性
var lightPosition = vec4(0.5,0.5,0.0, 0.0 );
var lightAmbient = vec4(0.2, 0, 0.2, 1.0 );
var lightDiffuse = vec4( 1.0, 1.0, 1.0, 1.0 );
var lightSpecular = vec4( 1.0, 1.0, 1.0, 1.0 );
//反射系数
var materialAmbient = vec4( 1.0,1.0,1.0, 1.0);
var materialDiffuse = vec4( 1.0, 0.8, 1.0, 1.0 );
var materialSpecular = vec4( 1.0, 1.0, 1.0, 1.0 );
var materialShininess = 50.0;

var ctm;
//单个光源的参数
var ambientColor, diffuseColor, specularColor;
var modelView, projection;
var viewerPos;


var vertices = [
//身体1，都是一些坐标
        vec3( -0.4,0.17,0.17),
        vec3( -0.6,-0.17,0.17),
        vec3( -0.2,-0.17,0.17),
        vec3( -0.4,-0.17,-0.17),

//嘴巴1
        vec3( -0.3,-0.07,0.17),
        vec3( -0.4,-0.14,0.17),
        vec3( -0.5,-0.07,0.17),
        vec3( -0.4,0.0,0.17),
        vec3(-0.4,-0.07,0.27),
        vec3(-0.4,-0.07,0.37),

        //身体2
       vec3( 0.4,0.17,0.17),
        vec3( 0.2,-0.17,0.17),
        vec3( 0.6,-0.17,0.17),
        vec3( 0.4,-0.17,-0.17),

    //嘴巴2
        vec3( 0.5,-0.07,0.17),
        vec3( 0.4,-0.14,0.17),
        vec3( 0.3,-0.07,0.17),
        vec3( 0.4,0.0,0.17),
        vec3( 0.4,-0.07,0.27),
        vec3( 0.4,-0.07,0.37),

        //眉毛右1
         vec3(-0.36,0.0,0.18),
        vec3(-0.36,0.02,0.18),
        vec3( -0.28,0.04,0.18),
        vec3( -0.30,0.06,0.18),

        vec3( -0.30,0.06,0.16),
        vec3( -0.28,0.04,0.16),
         vec3(-0.36,0.02,0.16),
        vec3(-0.36,0.00,0.16),
        //眉毛左1
        vec3(-0.44,0.0,0.18),
        vec3(-0.44,0.02,0.18),
        vec3( -0.52,0.04,0.18),
        vec3( -0.50,0.06,0.18),

        vec3( -0.50,0.06,0.16),
        vec3( -0.52,0.04,0.16),
         vec3(-0.44,0.02,0.16),
        vec3(-0.44,0.0,0.16),

       //眉毛右2
        vec3(0.36,0.0,0.18),
        vec3(0.36,0.02,0.18),
        vec3( 0.28,0.04,0.18),
        vec3( 0.30,0.06,0.18),

        vec3( 0.30,0.06,0.16),
        vec3( 0.28,0.04,0.16),
         vec3(0.36,0.02,0.16),
        vec3(0.36,0.00,0.16),
        //眉毛左2
        vec3(0.44,0.0,0.18),
        vec3(0.44,0.02,0.18),
        vec3(0.52,0.04,0.18),
        vec3(0.50,0.06,0.18),

        vec3(0.50,0.06,0.16),
        vec3(0.52,0.04,0.16),
         vec3(0.44,0.02,0.16),
        vec3(0.44,0.0,0.16),
       

    ];

//颜色
    var vertexColors = [
    //身体1
        vec4( 1.0, 0.9, 0.0, 0.8 ),  // yellow
        vec4( 1.0, 0.9, 0.0, 0.8 ),  // yellow
        vec4( 1.0, 0.9, 0.0, 0.8 ),  // yellow
        vec4( 1.0, 0.9, 0.0, 0.8 ),  // yellow
//嘴巴1
        vec4( 1.0, 0.9, 0.0, 1.0 ),  // yellow
        vec4( 1.0, 0.9, 0.0, 1.0 ),  // yellow
        vec4( 1.0, 0.9, 0.0, 1.0 ),  // yellow
        vec4( 1.0, 0.9, 0.0, 1.0 ),  // yellow
        vec4( 1.0, 0.9, 0.0, 1.0 ),  // yellow
        vec4( 1.0, 0.9, 0.0, 1.0 ),   // yellow
//身体2
        vec4( 1.0, 0.9, 0.0, 0.8 ),  // yellow
        vec4( 1.0, 0.9, 0.0, 0.8 ),  // yellow
        vec4( 1.0, 0.9, 0.0, 0.8 ),  // yellow
        vec4( 1.0, 0.9, 0.0, 0.8 ),  // yellow
//嘴巴2
        vec4( 1.0, 0.9, 0.0, 1.0 ),  // yellow
        vec4( 1.0, 0.9, 0.0, 1.0 ),  // yellow
        vec4( 1.0, 0.9, 0.0, 1.0 ),  // yellow
        vec4( 1.0, 0.9, 0.0, 1.0 ),  // yellow
        vec4( 1.0, 0.9, 0.0, 1.0 ),  // yellow
        vec4( 1.0, 0.9, 0.0, 1.0 ),   // yellow
        //眉毛1 
        vec4( 1.0, 0.0, 0.0, 1.0 ),//red
        vec4( 1.0, 0.0, 0.0, 1.0 ),//red
        vec4( 1.0, 0.0, 0.0, 1.0 ),//red
        vec4( 1.0, 0.0, 0.0, 1.0 ),//red
        vec4( 1.0, 0.0, 0.0, 1.0 ),//red
        vec4( 1.0, 0.0, 0.0, 1.0 ),//red
        vec4( 1.0, 0.0, 0.0, 1.0 ),//red
        vec4( 1.0, 0.0, 0.0, 1.0 ),//red

        vec4( 1.0, 0.0, 0.0, 1.0 ),//red
        vec4( 1.0, 0.0, 0.0, 1.0 ),//red
        vec4( 1.0, 0.0, 0.0, 1.0 ),//red
        vec4( 1.0, 0.0, 0.0, 1.0 ),//red
        vec4( 1.0, 0.0, 0.0, 1.0 ),//red
        vec4( 1.0, 0.0, 0.0, 1.0 ),//red
        vec4( 1.0, 0.0, 0.0, 1.0 ),//red
        vec4( 1.0, 0.0, 0.0, 1.0 ),//red

vec4( 1.0, 0.0, 0.0, 1.0 ),//red
        vec4( 1.0, 0.0, 0.0, 1.0 ),//red
        vec4( 1.0, 0.0, 0.0, 1.0 ),//red
        vec4( 1.0, 0.0, 0.0, 1.0 ),//red
        vec4( 1.0, 0.0, 0.0, 1.0 ),//red
        vec4( 1.0, 0.0, 0.0, 1.0 ),//red
        vec4( 1.0, 0.0, 0.0, 1.0 ),//red
        vec4( 1.0, 0.0, 0.0, 1.0 ),//red

        vec4( 1.0, 0.0, 0.0, 1.0 ),//red
        vec4( 1.0, 0.0, 0.0, 1.0 ),//red
        vec4( 1.0, 0.0, 0.0, 1.0 ),//red
        vec4( 1.0, 0.0, 0.0, 1.0 ),//red
        vec4( 1.0, 0.0, 0.0, 1.0 ),//red
        vec4( 1.0, 0.0, 0.0, 1.0 ),//red
        vec4( 1.0, 0.0, 0.0, 1.0 ),//red
        vec4( 1.0, 0.0, 0.0, 1.0 ),//red


       


    ];

// indices of the 12 triangles that compise the cube

var indices = [//索引，用来画立方体
//身体1
    0,1,2,
    0,2,3,
    0,3,1,
    1,3,2,

//嘴巴1
    4,5,6,
    4,6,7,
    7,6,9,
    7,9,4,
    6,4,9,
    6,5,8,
    4,8,5,
    6,4,8,
//身体2
    10,11,12,
    10,12,13,
    10,13,11,
    11,13,12,
//嘴巴2
    14,15,16,
    14,16,17,
    17,16,19,
    17,19,14,
    16,14,19,
    16,15,18,
    14,18,15,
    16,14,18,

//眉毛1
21,20,22,
22,23,21,
23,22,25,
25,24,23,
20,27,25,
25,22,20,
26,21,23,
23,24,26,
24,25,27,
27,26,24,
26,27,20,
20,21,26,

//眉毛2

29,28,30,
30,31,29,
31,30,33,
33,32,31,
28,35,33,
33,30,28,
34,29,31,
31,32,34,
32,33,35,
35,34,32,
34,35,28,
28,29,34,

37,36,38,
38,39,37,
39,38,41,
41,40,39,
36,43,41,
41,38,36,
42,37,39,
39,40,42,
40,41,43,
43,42,40,
42,43,36,
36,37,42,

45,44,46,
46,47,45,
47,46,49,
49,48,47,
44,51,49,
49,46,44,
50,45,47,
47,48,50,
48,49,51,
51,50,48,
50,51,44,
44,45,50,






];
function triangle(a, b, c) {

     var t1 = subtract(vertices[b], vertices[a]);
     var t2 = subtract(vertices[c],vertices[a]);
     var normal = normalize(cross(t2, t1));
     normal = vec4(normal);
     normal[3]  = 0.0;

     normalsArray.push(normal);
     normalsArray.push(normal);
     normalsArray.push(normal);

}
function quad(a, b, c, d) {

     var t1 = subtract(vertices[b], vertices[a]);
     var t2 = subtract(vertices[c], vertices[b]);
     var normal = cross(t1, t2);
     var normal = vec3(normal);

     normalsArray.push(normal);
     normalsArray.push(normal);
     normalsArray.push(normal);
     normalsArray.push(normal);
     normalsArray.push(normal);
     normalsArray.push(normal);
}


function colorCube()
{
    
   //身体1
    triangle(0,1,2);
    triangle(0,2,3);
    triangle(0,3,1);
    triangle(1,3,2);

//嘴巴1
    triangle(4,5,6);
    triangle(4,6,7);
    triangle(7,6,9);
    triangle(7,9,4);
    triangle(6,4,9);
    triangle(6,5,8);
    triangle(4,8,5);
    triangle(6,4,8);
//身体2
    triangle(10,11,12);
    triangle(10,12,13);
    triangle(10,13,11);
    triangle(11,13,12);
//嘴巴2
    triangle(14,15,16);
    triangle(14,16,17);
    triangle(17,16,19);
    triangle(17,19,14);
    triangle(16,14,19);
    triangle(16,15,18);
    triangle(14,18,15);
    triangle(16,14,18);

//眉毛1
triangle(21,20,22);
triangle(22,23,21);
triangle(23,22,25);
triangle(25,24,23);
triangle(20,27,25);
triangle(25,22,20);
triangle(26,21,23);
triangle(23,24,26);
triangle(24,25,27);
triangle(27,26,24);
triangle(26,27,20);
triangle(20,21,26);

//眉毛2

triangle(29,28,30);
triangle(30,31,29);
triangle(31,30,33);
triangle(33,32,31);
triangle(28,35,33);
triangle(33,30,28);
triangle(34,29,31);
triangle(31,32,34);
triangle(32,33,35);
triangle(35,34,32);
triangle(34,35,28);
triangle(28,29,34);

triangle(37,36,38);
triangle(38,39,37);
triangle(39,38,41);
triangle(41,40,39);
triangle(36,43,41);
triangle(41,38,36);
triangle(42,37,39);
triangle(39,40,42);
triangle(40,41,43);
triangle(43,42,40);
triangle(42,43,36);
triangle(36,37,42);

triangle(45,44,46);
triangle(46,47,45);
triangle(47,46,49);
triangle(49,48,47);
triangle(44,51,49);
triangle(49,46,44);
triangle(50,45,47);
triangle(47,48,50);
triangle(48,49,51);
triangle(51,50,48);
triangle(50,51,44);
triangle(44,45,50);

}


window.onload = function init()
{
    canvas = document.getElementById( "gl-canvas" );

    gl = WebGLUtils.setupWebGL( canvas );
    if ( !gl ) { alert( "WebGL isn't available" ); }

    gl.viewport( 0, 0, canvas.width, canvas.height );
    aspect=canvas.width/canvas.height;
    gl.clearColor( 0, 0, 0, 1.0 );
    gl.enable(gl.DEPTH_TEST);
   
    var program = initShaders( gl, "vertex-shader", "fragment-shader" );
    gl.useProgram( program );

 drawEyes();
    // array element buffer

    colorCube();

    //  Load shaders and initialize attribute buffers
    






//环境光反射分量的每个分量=环境光各个分量*材质反射属性各个分量
    var ambientProduct = mult(lightAmbient, materialAmbient);
    var diffuseProduct = mult(lightDiffuse, materialDiffuse);
    var specularProduct = mult(lightSpecular, materialSpecular);
//





    var iBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, iBuffer);
    gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint8Array(indices), gl.STATIC_DRAW);


/////normalArray
 var nBuffer = gl.createBuffer();
    gl.bindBuffer( gl.ARRAY_BUFFER, nBuffer);
    gl.bufferData( gl.ARRAY_BUFFER, flatten(normalsArray), gl.STATIC_DRAW );


    var vNormal = gl.getAttribLocation( program, "vNormal" );
    gl.vertexAttribPointer( vNormal, 4, gl.FLOAT, false, 0, 0 );
    gl.enableVertexAttribArray( vNormal);

    // color array atrribute buffer

    var cBuffer = gl.createBuffer();
    gl.bindBuffer( gl.ARRAY_BUFFER, cBuffer );
    gl.bufferData( gl.ARRAY_BUFFER, flatten(vertexColors), gl.STATIC_DRAW );

    var vColor = gl.getAttribLocation( program, "vColor" );
    gl.vertexAttribPointer( vColor, 4, gl.FLOAT, false, 0, 0 );
    gl.enableVertexAttribArray( vColor );

    // vertex array attribute buffer

    var vBuffer = gl.createBuffer();
    gl.bindBuffer( gl.ARRAY_BUFFER, vBuffer );
    gl.bufferData( gl.ARRAY_BUFFER, flatten(vertices), gl.STATIC_DRAW );

    var vPosition = gl.getAttribLocation( program, "vPosition" );
    gl.vertexAttribPointer( vPosition, 3, gl.FLOAT, false, 0, 0 );
    gl.enableVertexAttribArray( vPosition );


    modelView = gl.getUniformLocation( program, "modelView" );
    projection = gl.getUniformLocation( program, "projection" );


    
    normalMatrixLoc = gl.getUniformLocation( program, "normalMatrix" );

    gl.uniform4fv( gl.getUniformLocation(program,
       "ambientProduct"),flatten(ambientProduct) );
    gl.uniform4fv( gl.getUniformLocation(program,
       "diffuseProduct"),flatten(diffuseProduct) );
    gl.uniform4fv( gl.getUniformLocation(program,
       "specularProduct"),flatten(specularProduct) );
    gl.uniform4fv( gl.getUniformLocation(program,
       "lightPosition"),flatten(lightPosition) );
    gl.uniform1f( gl.getUniformLocation(program,
       "shininess"),materialShininess );

   //response for buttons
    document.getElementById("Button1").onclick = function(){near  *= 1.1; far *= 1.1;};
    document.getElementById("Button2").onclick = function(){near *= 0.9; far *= 0.9;};
    document.getElementById("Button3").onclick = function(){radius *= 1.1;};
    document.getElementById("Button4").onclick = function(){radius *= 0.9;};
    document.getElementById("Button5").onclick = function(){theta += dr;};
    document.getElementById("Button6").onclick = function(){theta -= dr;};
    document.getElementById("Button7").onclick = function(){phi += dr;};
    document.getElementById("Button8").onclick = function(){phi -= dr;};
    document.getElementById("Button9").onclick = function(){selection=1;};
    document.getElementById("Button10").onclick = function(){selection=2;};
    document.getElementById("slider8").onchange = function(event) {
        materialAmbient = vec4(parseInt(event.target.value)/20,
                            (parseInt(event.target.value)+1)/20*255,
                            parseInt(event.target.value)/20,
                            parseInt(event.target.value)/20);
        var ambientProduct = mult(lightAmbient, materialAmbient);
    gl.uniform4fv(gl.getUniformLocation(program, "ambientProduct"),
       flatten(ambientProduct));
    }
    //9 强度
    document.getElementById("slider9").onchange = function(event){
        lightAmbient = vec4(parseInt(event.target.value)/20,
                            (parseInt(event.target.value)+1)/20*255,
                            parseInt(event.target.value)/20,
                            parseInt(event.target.value)/20);
        var ambientProduct = mult(lightAmbient,materialAmbient);
        gl.uniform4fv(gl.getUniformLocation(program,"ambientProduct"),flatten(ambientProduct));
    }
    //10 位置
    document.getElementById("slider10").onchange = function(event){
        var _theta= 2*Math.PI*parseInt(event.target.value)/20;
        var _y = Math.sin(_theta);
        var _x = Math.cos(_theta);
        lightPosition = vec4(_x,_y,0.0,1.0);
        gl.uniform4fv(gl.getUniformLocation(program, "lightPosition"),
       flatten(lightPosition) );
    }
   


    render();
}


function drawEyes()
{
     left_eye1 = ball(-0.48, -0.03, 0.18, 0.035, 255, 255, 255); //左眼1
    right_eye1 = ball(-0.32, -0.03, 0.18, 0.035, 255, 255, 255); //右眼1
    left_eye2 = ball(0.32, -0.03, 0.18, 0.035, 255, 255, 255); //左眼2
    right_eye2 = ball(0.48, -0.03, 0.18, 0.035, 255, 255, 255); //右眼2
    left_eye1_ball = ball(-0.48, -0.03, 0.205, 0.02, 0, 0, 0); //左眼珠1
    right_eye1_ball = ball(-0.32, -0.03, 0.205, 0.02, 0, 0, 0); //右眼珠1
    left_eye2_ball = ball(0.32, -0.03, 0.205, 0.02, 0, 0, 0); //左眼珠2
    right_eye2_ball = ball(0.48, -0.03, 0.205, 0.02, 0, 0, 0); //右眼珠2

}
function render()//进行平移，变换的一些实现
{
    gl.clear( gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

if(selection==1){
        eye = vec3(radius*Math.sin(phi), radius*Math.sin(theta),
                   radius*Math.cos(phi));

        modelViewMatrix = lookAt(eye, at , up);
        projectionMatrix = ortho(left, right, bottom, ytop, near, far);

        gl.uniformMatrix4fv( modelView, false, flatten(modelViewMatrix) );
        gl.uniformMatrix4fv( projection, false, flatten(projectionMatrix) );
    }
    if(selection==2){
        eye = vec3(radius*Math.sin(theta)*Math.cos(phi),
            radius*Math.sin(theta)*Math.sin(phi), radius*Math.cos(theta));
        modelViewMatrix = lookAt(eye, at , up);
        projectionMatrix = perspective(fovy, aspect, near, far);

        gl.uniformMatrix4fv( modelView ,false, flatten(modelViewMatrix) );
        gl.uniformMatrix4fv( projection, false, flatten(projectionMatrix) );
    }

//end

    gl.drawElements( gl.TRIANGLES, vertexNum, gl.UNSIGNED_BYTE, 0 );
    var Length = 108;
    Length = drawball(Length, left_eye1);
    Length = drawball(Length, right_eye1);
    Length = drawball(Length, left_eye2);
    Length = drawball(Length, right_eye2);
    Length = drawball(Length, left_eye1_ball);
    Length = drawball(Length, right_eye1_ball);
    Length = drawball(Length, left_eye2_ball);
    Length = drawball(Length, right_eye2_ball);
    gl.drawArrays(gl.TRIANGLE_FAN, Length, right_eye2_ball);
    id = requestAnimFrame(render);
}
//得到球
function ball(x, y, z, r, color1, color2, color3) {
    var _x = 0;
    var _y = 0;
    var _z = 0;
    var length1 = 0;
    for (var i = 89; i > -89; i--) {
        if (i == 89) {
            vertices.push(vec3(x, y, z + r));
            vertexColors.push(vec4(color1 / 255, color2 / 255, color3 / 255, 1));

            //法向量
            var t1=subtract(vec3(x,y,z),vec3(x, y, z + r));
            var normal=normalize(t1);
            normal=vec4(normal);
            normal[3]=0;
            normalsArray.push(normal);

            for (var j = 0; j <= 360; j++) {
                _x = x + r * Math.sin(Math.PI / 180 * j) * Math.cos(i / 180 * Math.PI);
                _y = y + r * Math.cos(Math.PI / 180 * j) * Math.cos(Math.PI / 180 * i);
                _z = z + r * Math.sin(Math.PI / 180 * i);
                vertices.push(vec3(_x, _y, _z));
                vertexColors.push(vec4(color1 / 255, color2 / 255, color3 / 255, 1));

                //法向量
                var t1=subtract(vec3(x,y,z),vec3(_x, _y, _z));
                var normal=normalize(t1);
                normal=vec4(normal);
                normal[3]=0;
                normalsArray.push(normal);
            }
        }
        for (var j = 0; j <= 360; j++) {
            length1 += 2;
            _x = x + r * Math.sin(Math.PI / 180 * j) * Math.cos(Math.PI / 180 * i);
            _y = y + r * Math.cos(Math.PI / 180 * j) * Math.cos(Math.PI / 180 * i);
            _z = z + r * Math.sin(Math.PI / 180 * i);
            vertices.push(vec3(_x, _y, _z));
            vertexColors.push(vec4(color1 / 255, color2 / 255, color3 / 255, 1));

            //法向量
            var t1=subtract(vec3(x,y,z),vec3(_x, _y, _z));
            var normal=normalize(t1);
            normal=vec4(normal);
            normal[3]=0;
            normalsArray.push(normal);

            _x = x + r * Math.sin(Math.PI / 180 * j) * Math.cos(Math.PI / 180 * (i - 1));
            _y = y + r * Math.cos(Math.PI / 180 * j) * Math.cos(Math.PI / 180 * (i - 1));
            _z = z + r * Math.sin(Math.PI / 180 * (i - 1));
            vertices.push(vec3(_x, _y, _z));
            vertexColors.push(vec4(color1 / 255, color2 / 255, color3 / 255, 1));

            //法向量
            var t1=subtract(vec3(x,y,z),vec3(_x, _y, _z));
            var normal=normalize(t1);
            normal=vec4(normal);
            normal[3]=0;
            normalsArray.push(normal);
        }
        if (i == -88) {
            vertices.push(vec3(x, y, z - r));
            vertexColors.push(vec4(color1 / 255, color2 / 255, color3 / 255, 1));

            //法向量
            var t1=subtract(vec3(x,y,z),vec3(x, y, z - r));
            var normal=normalize(t1);
            normal=vec4(normal);
            normal[3]=0;
            normalsArray.push(normal);

            for (var j = 0; j <= 360; j++) {
                _x = x + r * Math.sin(Math.PI / 180 * j) * Math.cos(Math.PI / 180 * (i + 1));
                _y = y + r * Math.cos(Math.PI / 180 * j) * Math.cos(Math.PI / 180 * (i + 1));
                _z = z + r * Math.sin(Math.PI / 180 * (i - 1));
                vertices.push(vec3(_x, _y, _z));
                vertexColors.push(vec4(color1 / 255, color2 / 255, color3 / 255, 1));

                //法向量
                var t1=subtract(vec3(x,y,z),vec3(_x, _y, _z));
                var normal=normalize(t1);
                normal=vec4(normal);
                normal[3]=0;
                normalsArray.push(normal);
            }
        }
    }
    return length1;
}


//画球
function drawball(m, length) {
    gl.drawArrays(gl.TRIANGLE_FAN, m, 362);
    gl.drawArrays(gl.TRIANGLE_STRIP, m + 362, length);
    gl.drawArrays(gl.TRIANGLE_FAN, m + 362 + length, 362);

    return length + m + 362 + 362;
}

