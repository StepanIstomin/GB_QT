function Coordinates() {
    this.points = 0;
    this.xSteps = 0;
    this.ySteps = 0;
    this.array = [];

    this.getCoord = function (figure)  {
        switch(figure)
        {
        case "Star":
            this.xSteps = 10;
            this.ySteps = 10;
            this.array = [
                        [5, 2],
                        [6, 4],
                        [8, 5],
                        [6, 6],
                        [5, 8],
                        [4, 6],
                        [2, 5],
                        [4, 4],
                        [5, 2],
                    ]
            break;
        case "Circle":
            this.xSteps = 6;
            this.ySteps = 6;
            this.array = [
                        [3, 3],
                        [2]
                    ]
            break;
        case "House":
            this.xSteps = 4;
            this.ySteps = 5;
            this.array = [
                        [1, 2],
                        [2, 1],
                        [3, 2],
                        [3, 4],
                        [1, 4],
                        [1, 2],
                    ]
            break;
        case "Sandglass":
            this.xSteps = 3;
            this.ySteps = 8;
            this.array = [
                        [1, 1],
                        [2, 1],
                        [2, 3],
                        [1, 5],
                        [1, 7],
                        [2, 7],
                        [2, 5],
                        [1, 3],
                        [1, 1],
                    ]
            break;
        default:
        }
        this.points = this.array.length
        return this.array;
    }

    this.getParams = function(){
        return Array(this.points,this.xSteps,this.ySteps)
    }

}
