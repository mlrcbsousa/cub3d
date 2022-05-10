/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.java                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 22:13:27 by msousa            #+#    #+#             */
/*   Updated: 2022/05/10 22:15:30 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

public void render()
{
  drawBackground();
  drawOverheadMap();

  int verticalGrid;
  int horizontalGrid;
  int distToNextVerticalGrid;
  int distToNextHorizontalGrid;
  float xIntersection;
  float yIntersection;
  float distToNextXIntersection;
  float distToNextYIntersection;

  int xGridIndex;
  int yGridIndex;

  float distToVerticalGridBeingHit;
  float distToHorizontalGridBeingHit;

  int castArc, castColumn;

  castArc = fPlayerArc;
  castArc-=ANGLE30;
  if (castArc < 0) {
    castArc=ANGLE360 + castArc;
  }

  for (castColumn=0; castColumn<PROJECTIONPLANEWIDTH; castColumn+=5)
  {
    if (castArc > ANGLE0 && castArc < ANGLE180)
    {
      horizontalGrid = (fPlayerY/TILE_SIZE)*TILE_SIZE  + TILE_SIZE;
      distToNextHorizontalGrid = TILE_SIZE;
      float xtemp = fITanTable[castArc] * (horizontalGrid - fPlayerY);
      xIntersection = xtemp + fPlayerX;
    }
    else
    {
      horizontalGrid = (fPlayerY/TILE_SIZE)*TILE_SIZE;
      distToNextHorizontalGrid = -TILE_SIZE;
      float xtemp = fITanTable[castArc] * (horizontalGrid - fPlayerY);
      xIntersection = xtemp + fPlayerX;
      horizontalGrid--;
    }

    if (castArc==ANGLE0 || castArc==ANGLE180)
    {
      distToHorizontalGridBeingHit=9999999F;
    }
    else
    {
      distToNextXIntersection = fXStepTable[castArc];
      while (true)
      {
        xGridIndex = (int)(xIntersection / TILE_SIZE);
        yGridIndex = (horizontalGrid / TILE_SIZE);

        if ((xGridIndex>=MAP_WIDTH) || (yGridIndex>=MAP_HEIGHT) || xGridIndex<0 || yGridIndex<0)
        {
          distToHorizontalGridBeingHit = Float.MAX_VALUE;
          break;
        }
        else if ((fMap[yGridIndex*MAP_WIDTH+xGridIndex])!=O)
        {
          distToHorizontalGridBeingHit  = (xIntersection-fPlayerX)*fICosTable[castArc];
          break;
        }
        else
        {
          xIntersection += distToNextXIntersection;
          horizontalGrid += distToNextHorizontalGrid;
        }
      }
    }

    // FOLLOW X RAY
    if (castArc < ANGLE90 || castArc > ANGLE270)
    {
      verticalGrid = TILE_SIZE + (fPlayerX/TILE_SIZE)*TILE_SIZE;
      distToNextVerticalGrid = TILE_SIZE;

      float ytemp = fTanTable[castArc]*(verticalGrid - fPlayerX);
      yIntersection = ytemp + fPlayerY;
    }
    else
    {
      verticalGrid = (fPlayerX/TILE_SIZE)*TILE_SIZE;
      distToNextVerticalGrid = -TILE_SIZE;

      float ytemp = fTanTable[castArc]*(verticalGrid - fPlayerX);
      yIntersection = ytemp + fPlayerY;

      verticalGrid--;
    }
    if (castArc==ANGLE90||castArc==ANGLE270)
    {
      distToVerticalGridBeingHit = 9999999;
    }
    else
    {
      distToNextYIntersection = fYStepTable[castArc];
      while (true)
      {
        xGridIndex = (verticalGrid/TILE_SIZE);
        yGridIndex = (int)(yIntersection/TILE_SIZE);

        if ((xGridIndex>=MAP_WIDTH) ||
          (yGridIndex>=MAP_HEIGHT) ||
          xGridIndex<0 || yGridIndex<0)
        {
          distToVerticalGridBeingHit = Float.MAX_VALUE;
          break;
        }
        else if ((fMap[yGridIndex*MAP_WIDTH+xGridIndex])!=O)
        {
          distToVerticalGridBeingHit =(yIntersection-fPlayerY)*fISinTable[castArc];
          break;
        }
        else
        {
          yIntersection += distToNextYIntersection;
          verticalGrid += distToNextVerticalGrid;
        }
      }
    }

        // DRAW THE WALL SLICE
        float scaleFactor;
        float dist;
    int topOfWall;
    int bottomOfWall;

    if (distToHorizontalGridBeingHit < distToVerticalGridBeingHit)
        {
          drawRayOnOverheadMap(xIntersection, horizontalGrid);
      dist=distToHorizontalGridBeingHit;
      fOffscreenGraphics.setColor(Color.gray);
    }
        else
        {
          drawRayOnOverheadMap(verticalGrid, yIntersection);
      dist=distToVerticalGridBeingHit;
      fOffscreenGraphics.setColor(Color.darkGray);
        }

    dist /= fFishTable[castColumn];
        int projectedWallHeight=(int)(WALL_HEIGHT*(float)fPlayerDistanceToTheProjectionPlane/dist);
    bottomOfWall = fProjectionPlaneYCenter+(int)(projectedWallHeight*0.5F);
    topOfWall = PROJECTIONPLANEHEIGHT-bottomOfWall;
        if (bottomOfWall>=PROJECTIONPLANEHEIGHT)
              bottomOfWall=PROJECTIONPLANEHEIGHT-1;
        fOffscreenGraphics.fillRect(castColumn, topOfWall, 5, projectedWallHeight);

        // TRACE THE NEXT RAY
        castArc+=5;
        if (castArc>=ANGLE360)
              castArc-=ANGLE360;
  }

  paint(getGraphics());
}
