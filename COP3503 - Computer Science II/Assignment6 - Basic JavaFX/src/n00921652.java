/**
 * COP3503, Assignment 6
 * Travis Gibson, n00921652
 *
 * NOTE: Very sorry for the messiness ahead of time, I ran out of time to clean up and flesh this out some more :(
 */

import java.awt.*;
import java.util.Calendar;
import java.util.GregorianCalendar;

import javafx.geometry.VPos;
import javafx.scene.layout.Pane;
import javafx.scene.layout.GridPane;
import javafx.scene.paint.Color;
import javafx.scene.shape.*;
import javafx.scene.text.Text;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.text.TextAlignment;
import javafx.stage.Stage;
import javafx.scene.layout.HBox;
import javafx.beans.property.SimpleDoubleProperty;
import javafx.beans.property.Property;
import javafx.beans.property.DoubleProperty;
import javafx.beans.property.ReadOnlyDoubleProperty;
import java.util.Random;
import javafx.scene.shape.ArcTo;
import javafx.scene.shape.Path;


public class n00921652 extends Application {
    @Override
    public void start(Stage primaryStage) {
        Random rng = new Random();
        ClockPane clockPane = new ClockPane(((Math.abs(rng.nextInt()) % 12) + 1), Math.abs(rng.nextInt()) % 60, Math.abs(rng.nextInt()) % 60);
        HangmanPane hangmanPane = new HangmanPane();

        HBox hbox = new HBox();
        hbox.setSpacing(20);
        Scene scene = new Scene(hbox, 600, 300);
        primaryStage.setScene(scene);
        clockPane.bindClockHeight(hbox.heightProperty());
        clockPane.bindClockWidth(hbox.widthProperty());
        hangmanPane.bindHangmanWidth(hbox.widthProperty());
        hangmanPane.bindHangmanHeight(hbox.heightProperty());

        hbox.getChildren().addAll(clockPane, hangmanPane);
        primaryStage.show();
    }

    public static void main(String[] args) {
        Application.launch(args);
    }
}

class ClockPane extends Pane {
    private int hour;
    private int minute;
    private int second;

    // Clock pane's width and height
    //private double w = 250, h = 250;
    private DoubleProperty width = new SimpleDoubleProperty();
    private DoubleProperty height = new SimpleDoubleProperty();

    /** Construct a default clock with the current time*/
    public ClockPane() {
        setCurrentTime();
    }

    /** Construct a clock with specified hour, minute, and second */
    public ClockPane(int hour, int minute, int second) {
        this.hour = hour;
        this.minute = minute;
        this.second = second;
        paintClock();
    }

    /** Return hour */
    public int getHour() {
        return hour;
    }

    /** Set a new hour */
    public void setHour(int hour) {
        this.hour = hour;
        paintClock();
    }

    /** Return minute */
    public int getMinute() {
        return minute;
    }

    /** Set a new minute */
    public void setMinute(int minute) {
        this.minute = minute;
        paintClock();
    }

    /** Return second */
    public int getSecond() {
        return second;
    }

    /** Set a new second */
    public void setSecond(int second) {
        this.second = second;
        paintClock();
    }

    /** Return clock pane's width */
    public double getClockWidth() {
        return width.doubleValue();
    }

    /** Set clock pane's width */
    public void setClockWidth(double w) {
        this.width.setValue(w);
        paintClock();
    }

    public void bindClockWidth(ReadOnlyDoubleProperty property) {
        this.width.bind(property.divide(3));
    }

    /** Return clock pane's height */
    public double getClockHeight() {
        return height.doubleValue();
    }

    /** Set clock pane's height */
    public void setClockHeight(double h) {
        this.height.setValue(h);
        paintClock();
    }

    public void bindClockHeight(ReadOnlyDoubleProperty property) {
        this.height.bind(property);
        paintClock();
    }

    /* Set the current time for the clock */
    public void setCurrentTime() {
        // Construct a calendar for the current date and time
        Calendar calendar = new GregorianCalendar();

        // Set current hour, minute and second
        this.hour = calendar.get(Calendar.HOUR_OF_DAY);
        this.minute = calendar.get(Calendar.MINUTE);
        this.second = calendar.get(Calendar.SECOND);

        paintClock(); // Repaint the clock
    }

    /** Paint the clock */
    private void paintClock() {
        // Draw circle
        Circle circle = new Circle();
        circle.centerXProperty().bind(width.divide(2));
        circle.centerYProperty().bind(height.divide(2));
        circle.radiusProperty().bind(width.divide(2));

        circle.setFill(Color.WHITE);
        circle.setStroke(Color.BLACK);

        Text t1 = new Text("12");
        t1.xProperty().bind(circle.radiusProperty().subtract(5));
        t1.yProperty().bind(circle.centerYProperty().subtract(circle.radiusProperty()).add(12));

        Text t2 = new Text("9");
        t2.xProperty().bind(circle.centerXProperty().subtract(circle.radiusProperty()).add(3));
        t2.yProperty().bind(circle.centerYProperty().add(5));

        Text t3 = new Text("3");
        t3.xProperty().bind(circle.centerXProperty().add(circle.radiusProperty()).subtract(10));
        t3.yProperty().bind(circle.centerYProperty().add(3));

        Text t4 = new Text("6");
        t4.xProperty().bind(circle.centerXProperty().subtract(3));
        t4.yProperty().bind(circle.centerYProperty().add(circle.radiusProperty()).subtract(3));

        Text timeText = new Text(hour + ":" + minute + ":" + second);
        timeText.setTextOrigin(VPos.CENTER);
        timeText.xProperty().bind(circle.centerXProperty().subtract(timeText.getLayoutBounds().getWidth() / 2));
        timeText.yProperty().bind(circle.centerYProperty().add(circle.radiusProperty().add(20)));

        Text nameText = new Text("Travis Gibson");
        nameText.setTextOrigin(VPos.CENTER);
        nameText.xProperty().bind(circle.centerXProperty().subtract(nameText.getLayoutBounds().getWidth() / 2));
        nameText.yProperty().bind(circle.centerYProperty());


        // Draw second hand
        DoubleProperty sLength = new SimpleDoubleProperty();
        sLength.bind(circle.radiusProperty().multiply(0.8));

        double secondHandMathSin = Math.sin(second * (2 * Math.PI / 60));
        double secondHandMathCos = Math.cos(second * (2 * Math.PI / 60));

        Line sLine = new Line();
        sLine.startXProperty().bind(circle.centerXProperty());
        sLine.startYProperty().bind(circle.centerYProperty());
        sLine.endXProperty().bind(circle.centerXProperty().add(sLength.multiply(secondHandMathSin)));
        sLine.endYProperty().bind(circle.centerYProperty().subtract(sLength.multiply(secondHandMathCos)));
        sLine.setStroke(Color.RED);

        // Draw minute hand
        DoubleProperty mLength = new SimpleDoubleProperty();
        mLength.bind(circle.radiusProperty().multiply(0.65));

        double minuteHandMathSin = Math.sin(minute * (2 * Math.PI / 60));
        double minuteHandMathCos = Math.cos(minute * (2 * Math.PI / 60));

        Line mLine = new Line();
        mLine.startXProperty().bind(circle.centerXProperty());
        mLine.startYProperty().bind(circle.centerYProperty());
        mLine.endXProperty().bind(circle.centerXProperty().add(mLength.multiply(minuteHandMathSin)));
        mLine.endYProperty().bind(circle.centerYProperty().subtract(mLength.multiply(minuteHandMathCos)));
        mLine.setStroke(Color.BLUE);

        // Draw hour hand
        DoubleProperty hLength = new SimpleDoubleProperty();
        hLength.bind(circle.radiusProperty().multiply(0.5));

        double hourHandMathSin = Math.sin((hour % 12 + minute / 60.0) * (2 * Math.PI / 12));
        double hourHandMathCos = Math.cos((hour % 12 + minute / 60.0) * (2 * Math.PI / 12));

        Line hLine = new Line();
        hLine.startXProperty().bind(circle.centerXProperty());
        hLine.startYProperty().bind(circle.centerYProperty());
        hLine.endXProperty().bind(circle.centerXProperty().add(hLength.multiply(hourHandMathSin)));
        hLine.endYProperty().bind(circle.centerYProperty().subtract(hLength.multiply(hourHandMathCos)));
        hLine.setStroke(Color.GREEN);

        getChildren().clear();
        getChildren().addAll(circle, nameText, t1, t2, t3, t4, timeText, mLine, hLine);
    }
}

class HangmanPane extends Pane {
    private DoubleProperty width = new SimpleDoubleProperty();
    private DoubleProperty height = new SimpleDoubleProperty();

    public double getHangmanWidth() {
        return width.doubleValue();
    }

    public double getHangmanHeight() {
        return height.doubleValue();
    }

    public DoubleProperty hangmanWidthProperty() {
        return this.width;
    }

    public DoubleProperty hangmanHeightProperty() {
        return this.height;
    }

    public void setHangmanWidth(double width) {
        this.width.setValue(width);
    }

    public void setHangmanHeight(double height) {
        this.height.setValue(height);
    }

    public void bindHangmanWidth(ReadOnlyDoubleProperty property) {
        this.width.bind(property.divide(3));
        drawHangmanPane();
    }

    public void bindHangmanHeight(ReadOnlyDoubleProperty property) {
        this.height.bind(property);
        drawHangmanPane();
    }

    public HangmanPane(double width, double height) {
        this.width.setValue(width);
        this.height.setValue(height);

        drawHangmanPane();
    }

    public HangmanPane() {

    }

    public void drawHangmanPane() {
        Path path = new Path();
        path.setStroke(Color.BLACK);
        path.setFill(Color.WHITE);
        MoveTo start = new MoveTo();
        start.xProperty().bind(width.multiply(0.5));
        start.yProperty().bind(height.multiply(0.9));

        ArcTo hill = new ArcTo();
        hill.xProperty().bind(width.multiply(0.1));
        hill.yProperty().bind(height.multiply(0.9));
        hill.radiusXProperty().bind(width.multiply(0.20));
        hill.radiusYProperty().bind(height.multiply(0.05));

        path.getElements().addAll(start, hill);

        Line postBody = new Line();
        postBody.startXProperty().bind(hill.xProperty().add(start.xProperty()).divide(2));
        postBody.startYProperty().bind(hill.yProperty().subtract(hill.radiusYProperty()));
        postBody.endXProperty().bind(hill.xProperty().add(start.xProperty()).divide(2));
        postBody.endYProperty().bind(height.multiply(0.1));
        postBody.setStroke(Color.BLACK);
        postBody.setFill(Color.BLACK);
        
        Line postHanging = new Line();
        postHanging.startXProperty().bind(postBody.endXProperty());
        postHanging.startYProperty().bind(postBody.endYProperty());
        postHanging.endXProperty().bind(width.multiply(0.75));
        postHanging.endYProperty().bind(postBody.endYProperty());
        postHanging.setStroke(Color.BLACK);
        postHanging.setFill(Color.BLACK);
        
        Line rope = new Line();
        rope.startXProperty().bind(postHanging.endXProperty());
        rope.startYProperty().bind(postHanging.endYProperty());
        rope.endXProperty().bind(postHanging.endXProperty());
        rope.endYProperty().bind(height.multiply(0.2));
        rope.setStroke(Color.BLACK);
        rope.setFill(Color.BLACK);

        Circle head = new Circle();
        head.radiusProperty().bind(width.multiply(0.10));
        head.centerXProperty().bind(rope.endXProperty());
        head.centerYProperty().bind(height.multiply(0.25));
        head.setStroke(Color.BLACK);
        head.setFill(Color.WHITE);

        Line body = new Line();
        body.startXProperty().bind(head.centerXProperty());
        body.startYProperty().bind(head.centerYProperty().add(head.radiusProperty()));
        body.endXProperty().bind(head.centerXProperty());
        body.endYProperty().bind(height.multiply(0.45));
        body.setStroke(Color.BLACK);
        body.setFill(Color.BLACK);
        
        Line leftArm = new Line();
        leftArm.startXProperty().bind(body.startXProperty());
        leftArm.startYProperty().bind(body.startYProperty());
        leftArm.endXProperty().bind(postHanging.startXProperty().add(postHanging.endXProperty()).divide(2));
        leftArm.endYProperty().bind(body.startYProperty().add(body.endYProperty()).divide(2));
        leftArm.setStroke(Color.BLACK);
        leftArm.setFill(Color.BLACK);

        Line rightArm = new Line();
        rightArm.startXProperty().bind(body.startXProperty());
        rightArm.startYProperty().bind(body.startYProperty());
        rightArm.endXProperty().bind(rightArm.startXProperty().add(postHanging.endXProperty().subtract(postHanging.startXProperty()).divide(2)));
        rightArm.endYProperty().bind(body.startYProperty().add(body.endYProperty()).divide(2));
        rightArm.setStroke(Color.BLACK);
        rightArm.setFill(Color.BLACK);

        Line leftLeg = new Line();
        leftLeg.startXProperty().bind(body.endXProperty());
        leftLeg.startYProperty().bind(body.endYProperty());
        leftLeg.endXProperty().bind(postHanging.startXProperty().add(postHanging.endXProperty()).divide(2));
        leftLeg.endYProperty().bind(body.endYProperty().add(body.endYProperty().subtract(body.startYProperty()).divide(2)));
        leftLeg.setStroke(Color.BLACK);
        leftLeg.setFill(Color.BLACK);

        Line rightLeg = new Line();
        rightLeg.startXProperty().bind(body.endXProperty());
        rightLeg.startYProperty().bind(body.endYProperty());
        rightLeg.endXProperty().bind(body.endXProperty().add(postHanging.endXProperty().subtract(postHanging.startXProperty()).divide(2)));
        rightLeg.endYProperty().bind(body.endYProperty().add(body.endYProperty().subtract(body.startYProperty()).divide(2)));
        rightLeg.setStroke(Color.BLACK);
        rightLeg.setFill(Color.BLACK);

        getChildren().clear();
        getChildren().addAll(path, postBody, postHanging, rope, head, body, leftArm, rightArm, leftLeg, rightLeg);
    }
}

//Didn't have time to finish :(
class FanPane extends Pane {
    private GridPane gridPane = new GridPane();
    private DoubleProperty width = new SimpleDoubleProperty();
    private DoubleProperty height = new SimpleDoubleProperty();

    public double getFanWidth() {
        return width.doubleValue();
    }

    public double getFanHeight() {
        return height.doubleValue();
    }

    public DoubleProperty fanWidthProperty() {
        return this.width;
    }

    public DoubleProperty fanHeightProperty() {
        return this.height;
    }

    public void setFanWidth(double width) {
        this.width.setValue(width);
    }

    public void setFanHeight(double height) {
        this.height.setValue(height);
    }

    public void bindFanWidth(ReadOnlyDoubleProperty property) {
        this.width.bind(property.divide(3));
        drawFanPane();
    }

    public void bindFanHeight(ReadOnlyDoubleProperty property) {
        this.height.bind(property);
        drawFanPane();
    }
    public void drawFanPane() {
        Circle circle = new Circle();
        circle.radiusProperty().bind(width.multiply(0.5));
        circle.setFill(Color.WHITE);
        circle.setStroke(Color.BLACK);

        Arc arc1 = new Arc();
        arc1.centerXProperty().bind(circle.centerXProperty().divide(2));
        arc1.centerYProperty().bind(circle.centerYProperty().divide(2));
    }
}
