#include "textoutput.h"

textOutput::textOutput(const QString &s, QWidget *parent) :
    QDialog(parent)
{
    scenePath = s;
    QString st = scenePath;
    QStringList sl = st.split('/');
    sceneDir = sl[sl.size()-2];
    readxml();
    exportPdf();
}

void textOutput::exportPdf()
{
    int teller;
    teller = 0;
    QString html;
    html = "<table width=\"100%\" border=\"1\" cellspacing=\"0\" cellpadding=\"5px\">";
    for (int i = 0 ;i < infoList.size();i++){
        teller += 1;
        QString s;
        QStringList sl;
        s = infoList[i][comment];
        sl = s.split('#');          // find linebreaks and set dialogue up nicely
        s = "";
        for (int j = 0; j < sl.size();j++){
            s +=  sl[j] + "<br>";
        }
        html += "<tr cellpadding=\"5px\"><td width=\"40%\" style=\"float:left;\"><img src=\""
                + scenePath + infoList[i][fileName]
                + "\" alt=\"dastoryboard pad\" width=\"200\" height=\"150\">"
                + "</td><td width=\"59%\">" + tr("Scene: ")
                + infoList[i][scene] + ", " + tr("Shot: ") + infoList[i][shot] + "<br><br>"
                + s
                + "</td></tr>";
        if (teller == 6){
            html += "</table><p>dastoryboard</p>"
                    "<table width=\"100%\" border=\"1\" cellspacing=\"0\" cellpadding=\"5px\">";
            teller = 0;
        }
    }
    html += "</table>";

    QTextDocument doc;
    doc.setHtml(html);
    QPrinter prn;
    prn.setOutputFileName(scenePath + sceneDir + ".pdf");
    prn.setOutputFormat(QPrinter::PdfFormat);
    prn.setColorMode(QPrinter::Color);
    prn.setPaperSize(QPrinter::A4);
    prn.setPageMargins(20,20,20,20,QPrinter::Millimeter);
    doc.print(&prn);
}

/*
 * Reads the necessary information from the xml-file, and loads them into the
 * appropriate variables:
 * fileName: Filename of image, without any path information
 * comment: Comment as a QString. If it holds any '#' this means line break
*/
void textOutput::readxml()
{
    framesTotal = 0;
    QFile sbFile(scenePath + sceneDir + ".dastoryboard");    // open the storyboard file
    if (sbFile.open(QIODevice::ReadOnly)){
        QXmlStreamReader xmlreader(&sbFile);
        while(!xmlreader.atEnd()){
            xmlreader.readNext();
            if (xmlreader.isStartElement() && xmlreader.name() == "fileName")
                infos.append(xmlreader.readElementText());
            else if (xmlreader.isStartElement() && xmlreader.name() == "comment")
                infos.append(xmlreader.readElementText());
            else if (xmlreader.isStartElement() && xmlreader.name() == "scene")
                infos.append(xmlreader.readElementText());
            else if (xmlreader.isStartElement() && xmlreader.name() == "shot")
                infos.append(xmlreader.readElementText());
            else if (xmlreader.isStartElement() && xmlreader.name() == "frames"){
                infos.append(xmlreader.readElementText());
                QPixmap im;
                if (im.load(scenePath + infos[fileName])){
                    pixmapList.append(im);  // add pixmap to pixmapList
                    framesTotal += infos[frames].toInt();   // sum up the FRAMES TOTAL
                    infoList.append(infos); // append infos to the infoList, and..
                    infos.clear();          // .. clear the infos
                }
            }
        }
        infos = infoList[0];
    }

}
