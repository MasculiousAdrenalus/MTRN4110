

typedef struct {
    int x,y;
}cords;
typedef struct {
    cords width, length;
    int a, b, c, d;
}rect;

class EncodeMaze {
    public:
    cords map_size;
    int maze_x = 9; //cells
    int maze_y= 5;
    cords pt1,pt2 = 0; //rectangular section to check
    double cell_x = 250; //mm
    double cell_y = 250;
    double var = 25;
    //class funcs
    EncodeMaze();
    ~EncodeMaze();
    void getMap(image maze_red);
    
}
EncodeMaze::EncodeMaze(){
    map_size.x = maze_x*cell_x;
    map_size.y = maze_x*cell_y;
}
~EncodeMaze::EncodeMaze(){}

void EncodeMaze::getMap(image maze_red) {
    //gets verticle
    for (int x =1; x < (maze_x-1); x++) {
        a=250*x-25;
        b=250*x+25;
        
        for (int y=1; y < (maze_y-1); y++) {
            
            c = 250*y-25;
            d = 250*y+25;
            pt1.x = a; pt1.y = c;
            pt2.x = b; pt2.y = d;
            rect = drawRectangle(pt1, pt2)
            rect_maze = drawRectangle(pt1, pt2) OR maze_red
            if (maze_red[:][:][2] AND rect_maze != 1){
                
            }
            
        }
    }
    
}
if (maze_red[x][y][2]==RED) {
    

}