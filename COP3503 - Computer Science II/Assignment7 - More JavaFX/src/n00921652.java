import javafx.animation.Animation;
import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.application.Application;
import javafx.beans.property.DoubleProperty;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.*;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.*;
import javafx.scene.media.Media;
import javafx.scene.media.MediaPlayer;
import javafx.scene.media.MediaView;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.scene.text.*;
import javafx.stage.Stage;
import javafx.util.Duration;

/**
 * Created by tgibson on 12/6/2014.
 */
public class n00921652 extends Application {
    public static void main(String[] args) {
        Application.launch(args);
    }

    @Override
    public void start(Stage primaryStage) throws Exception {
        BorderPane mainBorderPane = new BorderPane();
        GridPane centerGridPane = new GridPane();
        BouncingRectanglePane bouncingRectangle = new BouncingRectanglePane();
        TextPane textPane = new TextPane();

        //Splitting the center in half for the text and the video
        ColumnConstraints nameColumn = new ColumnConstraints();
        ColumnConstraints videoColumn = new ColumnConstraints();
        RowConstraints rowConstraint = new RowConstraints();
        nameColumn.setPercentWidth(50);
        nameColumn.setHalignment(HPos.CENTER);
        videoColumn.setPercentWidth(50);
        videoColumn.setHalignment(HPos.CENTER);
        rowConstraint.setValignment(VPos.CENTER);
        centerGridPane.getColumnConstraints().addAll(nameColumn, videoColumn);
        centerGridPane.addColumn(0, textPane.getNameText());
        centerGridPane.addColumn(1, new VideoPlayer());
        centerGridPane.getRowConstraints().addAll(rowConstraint);

        mainBorderPane.setTop(bouncingRectangle);
        mainBorderPane.setLeft(textPane.getTextStyleVBox());
        mainBorderPane.setRight(textPane.getTextColorsVBox());
        mainBorderPane.setCenter(centerGridPane);
        mainBorderPane.setBottom(textPane.getButtonHBox());

        Scene mainScene = new Scene(mainBorderPane, 800, 400);

        primaryStage.setScene(mainScene);
        primaryStage.show();
    }
}

class BouncingRectanglePane extends Pane {
    private Rectangle rectangle;
    private Slider rectangleSpeedSlider;
    private Timeline bouncingAnimation;
    private HBox sliderHBox;
    private Label sliderLabel;
    private int deltaX = 1;
    private int deltaY = 1;

    BouncingRectanglePane() {
        rectangle = new Rectangle();
        rectangleSpeedSlider = new Slider();
        bouncingAnimation = new Timeline();
        sliderHBox = new HBox();
        sliderLabel = new Label("Speed: ");

        rectangle.setFill(Color.RED);
        rectangle.setWidth(50);
        rectangle.setHeight(25);
        rectangle.setX(1);
        rectangle.setY(1);

        rectangleSpeedSlider.setMin(0);
        rectangleSpeedSlider.setMax(100);
        rectangleSpeedSlider.setValue(50);
        rectangleSpeedSlider.setPrefWidth(200);
        rectangleSpeedSlider.setOrientation(Orientation.HORIZONTAL);
        sliderHBox.getChildren().addAll(sliderLabel, rectangleSpeedSlider);
        sliderHBox.setPrefWidth(800);
        sliderHBox.setAlignment(Pos.BOTTOM_CENTER);

        bouncingAnimation.getKeyFrames().add(0, new KeyFrame(Duration.millis(50), e -> moveRectangle()));
        bouncingAnimation.setCycleCount(Timeline.INDEFINITE);
        bouncingAnimation.rateProperty().bind(rectangleSpeedSlider.valueProperty().divide(10));
        bouncingAnimation.play();

        this.setHeight(100);
        this.getChildren().addAll(sliderHBox, rectangle);
        this.setPadding(new Insets(5.0, 5.0, 5.0, 5.0));
        sliderHBox.setLayoutY(this.getHeight() - sliderHBox.getHeight());
    }

    DoubleProperty getSpeedProperty() {
        return bouncingAnimation.rateProperty();
    }
    
    private void moveRectangle() {
        if (rectangle.getX() <= 0 ||
               rectangle.getX() >= this.getWidth() - rectangle.getWidth()) {
            deltaX *= -1;
        }
        if (rectangle.getY() <= 0 ||
               rectangle.getY() >= this.getHeight() - sliderHBox.getHeight() - rectangle.getHeight() - 5) {
            deltaY *= -1;
        }

        rectangle.setX(rectangle.getX() + deltaX);
        rectangle.setY(rectangle.getY() + deltaY);
    }
}

class VideoPlayer extends Pane {
    private Media video;
    private MediaPlayer videoPlayer;
    private MediaView videoView;
    private Button playButton;
    private Button rewindButton;
    private Slider volumeSlider;
    private HBox controlsHBox;
    private VBox videoVBox;
    private Label volumeLabel;

    VideoPlayer() {
        video = new Media("http://www.unf.edu/~n00921652/helsinkiinmotion.mp4");
        videoPlayer = new MediaPlayer(video);
        videoView = new MediaView(videoPlayer);
        playButton = new Button(">");
        rewindButton = new Button("<<");
        volumeSlider = new Slider();
        controlsHBox = new HBox();
        videoVBox = new VBox();
        volumeLabel = new Label("Volume:");

        playButton.setOnAction(e -> {
            if (playButton.getText().equals(">")) {
                videoPlayer.play();
                playButton.setText("||");
            }
            else {
                videoPlayer.pause();
                playButton.setText(">");
            }
        });

        rewindButton.setOnAction(e -> {
            videoPlayer.seek(Duration.ZERO);
        });

        volumeSlider.setMin(0);
        volumeSlider.setMax(100);
        volumeSlider.setValue(50);
        videoPlayer.volumeProperty().bind(volumeSlider.valueProperty().divide(100));

        videoView.setPreserveRatio(true);
        videoView.setFitWidth(300);

        controlsHBox.getChildren().addAll(playButton, rewindButton, volumeLabel, volumeSlider);
        controlsHBox.setAlignment(Pos.BOTTOM_CENTER);
        controlsHBox.setSpacing(10);

        videoVBox.getChildren().addAll(videoView, controlsHBox);
        videoVBox.setSpacing(10);
        this.getChildren().add(videoVBox);
        this.setPadding(new Insets(5.0, 5.0, 5.0, 5.0));
    }
}

class TextPane extends Pane {
    private Text nameText;
    private HBox buttonHBox;
    private VBox textStyleVBox;
    private VBox textColorsVBox;
    private Button upButton;
    private Button downButton;
    private Font normalFont;
    private Font boldFont;
    private Font italicFont;
    private Font boldItalicFont;
    private CheckBox boldCheckBox;
    private CheckBox italicCheckBox;
    private RadioButton orangeRadioButton;
    private RadioButton purpleRadioButton;
    private RadioButton greyRadioButton;
    private ToggleGroup colorsToggleGroup;
    private Label textStyleLabel;
    private Label textColorLabel;

    TextPane() {
        nameText = new Text("Travis Gibson");
        buttonHBox = new HBox();
        textStyleVBox = new VBox();
        textColorsVBox = new VBox();
        upButton = new Button("Move Text Up");
        downButton = new Button("Move Text Down");
        boldCheckBox = new CheckBox("Bold");
        italicCheckBox = new CheckBox("Italic");
        normalFont = Font.font("Verdana", FontWeight.NORMAL, FontPosture.REGULAR, 20);
        boldFont = Font.font("Verdana", FontWeight.BOLD, FontPosture.REGULAR, 20);
        italicFont = Font.font("Verdana", FontWeight.NORMAL, FontPosture.ITALIC, 20);
        boldItalicFont = Font.font("Verdana", FontWeight.BOLD, FontPosture.ITALIC, 20);
        orangeRadioButton = new RadioButton("Omaha Orange");
        purpleRadioButton = new RadioButton("Penelope Purple");
        greyRadioButton = new RadioButton("Gunmetal Grey");
        colorsToggleGroup = new ToggleGroup();
        textStyleLabel = new Label("Text Style:");
        textColorLabel = new Label("Text Color:");

        nameText.setFont(Font.font("Verdana", 20));
        nameText.setTextAlignment(TextAlignment.CENTER);

        //Setting up the up and down buttons
        upButton.setOnAction((e) -> {
            nameText.setTranslateY(nameText.getTranslateY() - 10);
        });

        downButton.setOnAction((e) -> {
            nameText.setTranslateY(nameText.getTranslateY() + 10);
        });

        buttonHBox.getChildren().addAll(upButton, downButton);
        buttonHBox.setAlignment(Pos.CENTER);
        buttonHBox.setPadding(new Insets(5.0, 5.0, 5.0, 5.0));
        buttonHBox.setSpacing(10);

        //Setting up the font style checkboxes
        EventHandler<ActionEvent> fontStyleHandler = e -> {
            if (boldCheckBox.isSelected() && italicCheckBox.isSelected()) {
                nameText.setFont(boldItalicFont);
            }
            else if (boldCheckBox.isSelected()) {
                nameText.setFont(boldFont);
            }
            else if (italicCheckBox.isSelected()) {
                nameText.setFont(italicFont);
            }
            else {
                nameText.setFont(normalFont);
            }
        };
        boldCheckBox.setOnAction(fontStyleHandler);
        italicCheckBox.setOnAction(fontStyleHandler);
        textStyleVBox.getChildren().addAll(textStyleLabel, boldCheckBox, italicCheckBox);
        textStyleVBox.setPadding(new Insets(5.0, 5.0, 5.0, 5.0));
        textStyleVBox.setSpacing(10);

        //Setting up the text color radiobuttons
        EventHandler<ActionEvent> fontColorHandler = e -> {
            if (orangeRadioButton.isSelected()) {
                nameText.setFill(Color.rgb(240, 60, 1));
            }
            else if (purpleRadioButton.isSelected()) {
                nameText.setFill(Color.rgb(161, 158, 189));
            }
            else {
                nameText.setFill(Color.rgb(82, 92, 110));
            }
        };
        orangeRadioButton.setOnAction(fontColorHandler);
        purpleRadioButton.setOnAction(fontColorHandler);
        greyRadioButton.setOnAction(fontColorHandler);

        orangeRadioButton.setToggleGroup(colorsToggleGroup);
        purpleRadioButton.setToggleGroup(colorsToggleGroup);
        greyRadioButton.setToggleGroup(colorsToggleGroup);

        //Activating orangeRadioButton as default
        orangeRadioButton.setSelected(true);
        nameText.setFill(Color.rgb(240, 60, 1));

        textColorsVBox.getChildren().addAll(textColorLabel, orangeRadioButton, purpleRadioButton, greyRadioButton);
        textColorsVBox.setPadding(new Insets(5.0, 5.0, 5.0, 5.0));
        textColorsVBox.setSpacing(10);
    }

    public HBox getButtonHBox() {
        return buttonHBox;
    }

    public VBox getTextStyleVBox() {
        return textStyleVBox;
    }

    public VBox getTextColorsVBox() {
        return textColorsVBox;
    }

    public Text getNameText() {
        return nameText;
    }
}
