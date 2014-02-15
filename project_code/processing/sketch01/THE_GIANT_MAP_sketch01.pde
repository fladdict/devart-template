float WIDTH = 800;
float HEIGHT = 800;

int COL = 30;  //Number of Nodes
int ROW = 30;
float colW;
float colH;

Node[][] nodes;

void setup()
{
  size(int(WIDTH), int(HEIGHT));
  colorMode(RGB,255);
  noStroke();
  reset();
}

void reset()
{
  nodes = new Node[ROW][COL];
  colW = WIDTH / float(COL-1);
  colH = HEIGHT / float(ROW-1);
  
  for(int y=0; y<ROW; y++){
    for(int x=0; x<COL; x++){
      Node nd = new Node();
      nd.x = nd.baseX = x * colW;
      nd.y = nd.baseY = y * colH;
      nd.z = 0;
      nodes[y][x] = nd;
    }
  }
}


void draw()
{
  background(0);
  updateNodes();
  drawNodes();
}

void updateNodes()
{
  for(int y=0; y<ROW; y++){
    for(int x=0; x<COL; x++){
      Node nd = nodes[y][x];
      float fx = (nd.baseX - nd.x)*0.1;
      float fy = (nd.baseY - nd.y)*0.1;
      nd.vx += fx;
      nd.vy += fy;
      nd.vx *= 0.98;
      nd.vy *= 0.98;
      nd.x += nd.vx;
      nd.y += nd.vy;
    }
  }
}

void drawNodes()
{
  for(int y=0; y<ROW; y++){
    for(int x=0; x<COL; x++){
      Node nd = nodes[y][x];
      float diameter = sqrt(nd.vx * nd.vx + nd.vy*nd.vy)*3+2;
      fill(255);
      ellipse(nd.x, nd.y, diameter,diameter);
    }
  }
}

void mouseMoved()
{
  float mx = mouseX;
  float my = mouseY;
  for(int y=0; y<ROW; y++){
    for(int x=0; x<COL; x++){
      Node nd = nodes[y][x];
      float dx = nd.x - mx;
      float dy = nd.y - my;
      float dist = sqrt(dx*dx+dy*dy);
      if(dist>1){
        dx = dx / dist / dist * 50;
        dy = dy / dist / dist * 50;
        nd.vx += dx;
        nd.vy += dy;
      }
    }
  }
}

void mousePressed()
{
  float mx = mouseX;
  float my = mouseY;
  for(int y=0; y<ROW; y++){
    for(int x=0; x<COL; x++){
      Node nd = nodes[y][x];
      float dx = nd.x - mx;
      float dy = nd.y - my;
      float dist = sqrt(dx*dx+dy*dy);
      if(dist>1){
        dx = dx / dist / dist * 400;
        dy = dy / dist / dist * 400;
        nd.vx += dx;
        nd.vy += dy;
      }
    }
  }
}


/***************************************
  Node
 ***************************************/

class Node
{
  float baseX = 0;
  float baseY = 0;
  float x = 0;
  float y = 0;
  float z = 0;
  float vx = 0;
  float vy = 0;
  float vz = 0;
}

